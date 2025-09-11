#pragma once
#ifndef NIBBLER_CONFIG
#define NIBBLER_CONFIG

#include <cstdint>
#include <string>
#include <vector>

namespace nibbler {

struct ConfigLibrary {
    std::string key;
    std::string name;
    std::string path;
};

struct Configuration {
    size_t window_width_pixels; // TODO: necessary?
    size_t window_height_pixels; // TODO: necessary?
    size_t gameboard_width_squares; // FIXME: comes from cli
    size_t gameboard_height_squares; // FIXME: comes from cli

    std::vector<ConfigLibrary> gui_libraries;
};

class ConfigParser {
public:
    static Configuration parseConfigFile(const std::string &file_path);
};

}

#endif