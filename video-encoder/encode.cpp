#include <opencv2/opencv.hpp>
#include <boost/tokenizer.hpp>
#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include "./image_processing.h"
#include "./cxxopts.hpp"
#define DELIMITER "FRM_E"


int main(int argc, char **argv) {
    std::string video_path;
    std::string output_path;
    ImageToAsciiOptions image_options;

    cxxopts::Options options("console-video-encoder", "A program to encode videos into ascii chars, "
        "playable in the console with `console-video-player`");

    options.add_options()
        ("i,input", "Path to input video", cxxopts::value<std::string>())
        ("o,output", "Path to output encoded video", cxxopts::value<std::string>())
        ("s,size", "Resolution of outputted video (width x height)", cxxopts::value<std::string>())
        ("c,colour", "Enable colour in outputted file using ANSI escape codes. Not supported in all terminals")
        ("h,help", "Show this message");

    auto args = options.parse(argc, argv);

    if (args.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (args.count("colour")) {
        image_options.colour = true;
    }

    video_path = args["input"].as<std::string>();
    output_path = args["output"].as<std::string>();

    if (args.count("size")) {
        auto size_str = args["size"].as<std::string>();
        boost::char_separator<char> sep("x");
        boost::tokenizer<boost::char_separator<char>> tok(size_str, sep);

        int width = 0, height = 0, count = 0;

        for (auto it = tok.begin(); it != tok.end() && count < 2; ++it, ++count) {
            std::stringstream ss(*it);
            if (!count) ss >> width; // Store width in the first iteration
            else ss >> height; // Store height in the second iteration
        }

        std::cout << "Width: " << width << ", Height: " << height << std::endl;
        image_options.output_width = width;
        image_options.output_height = height;
    }

    cv::VideoCapture video(video_path);
    auto fps = static_cast<uchar>(video.get(cv::CAP_PROP_FPS));
    printf("Video FPS: %i", fps);

    if (!video.isOpened()) {
        printf("Unable to open video");
        return 1;
    }

    std::ofstream output_file(output_path);
    cv::Mat frame;

    output_file << fps << '\0' << std::endl;

    for (;;) {
        video >> frame;
        if (frame.empty()) break;

        output_file << image_to_ascii(frame, image_options);
        output_file << DELIMITER << std::endl;
    }
    
    return 0;
}