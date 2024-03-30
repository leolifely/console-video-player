//
// Created by leoli on 30/03/24.
//

#ifndef IMAGE_TO_ASCII_H
#define IMAGE_TO_ASCII_H
#include <string>
#include <opencv2/core/mat.hpp>


struct ImageToAsciiOptions {
    std::string chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    int output_width = 160;
    int output_height = 48;
};

std::string image_to_ascii(const cv::Mat &image, const ImageToAsciiOptions &options);

#endif //IMAGE_TO_ASCII_H