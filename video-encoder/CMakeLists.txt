cmake_minimum_required(VERSION 3.10)
project(console-video-encoder)
find_package(OpenCV REQUIRED)
add_executable(console-video-encoder encode.cpp
        command_line.h
        command_line.cpp
        image_processing.h
        image_processing.cpp)
target_link_libraries(console-video-encoder PRIVATE ${OpenCV_LIBS})