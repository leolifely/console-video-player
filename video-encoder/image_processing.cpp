//
// Created by leoli on 30/03/24.
//
#include "image_processing.h"

#include <opencv2/imgproc.hpp>

std::string image_to_ascii(const cv::Mat &image, const ImageToAsciiOptions &options) {
    cv::Mat greyscale_image, processed_image;
    cvtColor(image, greyscale_image, cv::COLOR_BGR2GRAY);
    resize(greyscale_image, processed_image, cv::Size(options.output_width, options.output_height), cv::INTER_LINEAR);

    const auto num_chars = static_cast<int>(options.chars.size());

    std::string ascii_image;
    for (int row = 0; row < processed_image.rows; row++) {
        for (int col = 0; col < processed_image.cols; col++) {
            auto intensity = processed_image.at<uchar>(row, col);

            intensity = 255 - intensity;

            const auto index = static_cast<int>(static_cast<double>(intensity) / 255.0 * (num_chars - 1));
            ascii_image += options.chars[index];
        }
        ascii_image += '\n';
    }

    return ascii_image;
}
