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
    auto start_time = std::chrono::high_resolution_clock::now();
    while (std::getline(file_stream, line)) {
        auto end_time = std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
        if (line == DELIMITER) {
            double remaining_delay = delay - elapsed_time;
            if (remaining_delay > 0)
                std::this_thread::sleep_for(std::chrono::duration<double>(remaining_delay));
            start_time = std::chrono::high_resolution_clock::now();
        } else {
            std::cout << line << std::endl;
        }
    }
    return 0;
}
