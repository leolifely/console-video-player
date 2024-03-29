#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <SFML/Audio.hpp>

#define DELIMITER "FRM_E"

double get_fps(std::string file_path) {
    std::ifstream file(file_path, std::ios::binary);
    u_char fps_byte;
    file.read(reinterpret_cast<char*>(&fps_byte), sizeof(u_char));

    int fps = static_cast<double>(fps_byte);
    return fps;
}

void print_frame(std::vector<std::string> frame_data) {
    int number_lines = frame_data.size();
    std::string frame;

    for(int i = 0; i < number_lines; i++) {
        frame += frame_data[i];
    }

    std::cout << frame;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: play path_to_conv path_to_audio");
        return 1;
    }

    sf::SoundBuffer buffer;
    buffer.loadFromFile(argv[2]);
    sf::Sound sound(buffer);

    double fps = get_fps(argv[1]);
    double delay = 1.0 / fps;

    std::ifstream file_stream(argv[1]);

    std::vector<std::string> frame_data;
    std::string line;

    sound.play();
    while (std::getline(file_stream, line)) {
        if (line == DELIMITER) {
            std::this_thread::sleep_for(std::chrono::duration<double>(delay));
        } else {
            std::cout << line << std::endl;
        }
    }
}