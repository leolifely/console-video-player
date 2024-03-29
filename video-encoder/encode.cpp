#include <opencv4/opencv2/opencv.hpp>
#include <cstdio>
#include <string>
#include <fstream>


#define DELIMITER "FRM_E"



std::string image_to_ascii(const cv::Mat &image, const std::string &chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ") {
    const auto num_chars = static_cast<int>(chars.size());

    std::string ascii_art;
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            auto intensity = image.at<uchar>(i, j);

            intensity = 255 - intensity;

            const auto index = static_cast<int>(static_cast<double>(intensity) / 255.0 * (num_chars - 1));
            ascii_art += chars[index];
        }
        ascii_art += '\n';
    }

    return ascii_art;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: encode path_to_video output_path");
        return 1;
    }

    std::string video_path = argv[1];
    cv::VideoCapture video(video_path);
    auto fps = static_cast<uchar>(video.get(cv::CAP_PROP_FPS));
    printf("Video FPS: %i", fps);

    if (!video.isOpened()) {
        printf("Unable to open video");
        return 1;
    }
    
    std::ofstream output_file(argv[2]);
    cv::Mat full_size_frame, full_size_greyscale_frame, frame;

    output_file << fps << '\0' << std::endl;

    for (;;) {
        video >> full_size_frame;
        if (full_size_frame.empty()) break;
        
        cv::cvtColor(full_size_frame, full_size_greyscale_frame, cv::COLOR_BGR2GRAY);
       
        
        cv::resize(full_size_greyscale_frame, frame, cv::Size(160, 48), cv::INTER_LINEAR);
        


        output_file << image_to_ascii(frame);
        output_file << DELIMITER << std::endl;
    }
    
    return 0;
}