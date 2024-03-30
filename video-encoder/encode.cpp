#include <opencv4/opencv2/opencv.hpp>
#include <cstdio>
#include <string>
#include <fstream>
#include "image_processing.h"

#define DELIMITER "FRM_E"


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
    cv::Mat frame;

    output_file << fps << '\0' << std::endl;

    for (;;) {
        video >> frame;
        if (frame.empty()) break;

        output_file << image_to_ascii(frame, ImageToAsciiOptions{});
        output_file << DELIMITER << std::endl;
    }
    
    return 0;
}