#pragma once
#ifndef NIBBLER_CONFIG
#define NIBBLER_CONFIG

#include <cstdint>
#include <string>

namespace nibbler {

struct Configuration {
    uint32_t window_width;
    uint32_t window_height;
    uint32_t gameboard_width;
    uint32_t gameboard_height;
};

class ConfigParser {
public:
    static Configuration parseConfigFile(const std::string &file_path);
};

}

#endif