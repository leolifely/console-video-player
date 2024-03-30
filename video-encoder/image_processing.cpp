//
// Created by leoli on 30/03/24.
//
#include "image_processing.h"

#include <iostream>
#include <opencv2/imgproc.hpp>

std::string image_to_ascii(const cv::Mat &image, const ImageToAsciiOptions &options) {
    cv::Mat greyscale_image, resized_image;
    resize(image, resized_image, cv::Size(options.output_width, options.output_height), cv::INTER_LINEAR);
    uchar *ptr;
    int num_chars;
    if (!options.colour) {
        cvtColor(resized_image, greyscale_image, cv::COLOR_BGR2GRAY);
        num_chars = static_cast<int>(options.chars.size());
        ptr = greyscale_image.data;

    }


    std::string ascii_image;
    for (int row = 0; row < resized_image.rows; row++) {
        for (int col = 0; col < resized_image.cols; col++) {
            if (!options.colour) {
                int ptr_index = row * greyscale_image.cols + col;
                auto intensity = ptr[ptr_index];
                

                intensity = 255 - intensity;

                const auto index = static_cast<int>(static_cast<double>(intensity) / 255.0 * (num_chars - 1));
                ascii_image += options.chars[index];
            } else {
                ascii_image += "\x1b[38;2;" + std::to_string(static_cast<int>(resized_image.at<cv::Vec3b>(row, col)[2])) + ";" +
                               std::to_string(static_cast<int>(resized_image.at<cv::Vec3b>(row, col)[1])) + ";" +
                               std::to_string(static_cast<int>(resized_image.at<cv::Vec3b>(row, col)[0])) + "m█";
            }
        }
        ascii_image += '\n';
    }

    return ascii_image;
}
