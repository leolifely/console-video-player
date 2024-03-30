cmake_minimum_required(VERSION 3.10)
project(console-video-encoder)

find_package(OpenCV 4 REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(.)

add_executable(console-video-encoder encode.cpp image_processing.h image_processing.cpp cxxopts.hpp)

target_link_libraries(console-video-encoder
        ${OpenCV_LIBS}
        ${Boost_LIBRARIES}
        )

set_property(TARGET console-video-encoder PROPERTY CXX_STANDARD 17)