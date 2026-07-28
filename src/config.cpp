#include "config.hpp"
#include "nibbler/graphics_api.hpp"

#include "nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace nibbler {

Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    std::ifstream file(file_path);

    if (!file.good()) {
        std::cerr << "ERROR | file does not exist: " << file_path << std::endl;
        return config;
    }

    nlohmann::json data;
    try {
        data = nlohmann::json::parse(file);
    }
    catch (const std::exception &e) {
        std::cerr << "ERROR | invalid config file " << file_path << std::endl;
        return config;
    }

    if (!data.contains("gui_libraries")) {
        std::cerr << "ERROR | config file: missing property gui_libraries in " << file_path << std::endl;
        return config;
    }

    for (auto& element : data["gui_libraries"]) {
        if (!element.contains("key")) {
            std::cerr << "ERROR|> config file: gui_libraries element missing 'key' property in " << file_path << std::endl;
            continue;
        }
        if (!element.contains("name")) {
            std::cerr << "ERROR|> config file: gui_libraries element missing 'name' property in " << file_path << std::endl;
            continue;
        }
        if (!element.contains("path")) {
            std::cerr << "ERROR|> config file: gui_libraries element missing 'path' property in " << file_path << std::endl;
            continue;
        }
        if (!element.contains("resolution")) {
            std::cerr << "ERROR|> config file: gui_libraries element missing 'resolution' property in " << file_path << std::endl;
            continue;
        }
        if (!element["resolution"].contains("width")) {
            std::cerr << "ERROR|> config file: gui_libraries resolution element missing 'width' property in " << file_path << std::endl;
            continue;
        }
        if (!element["resolution"].contains("height")) {
            std::cerr << "ERROR|> config file: gui_libraries resolution element missing 'height' property in " << file_path << std::endl;
            continue;
        }

        if (element["key"].is_number()) {
            std::cerr << "ERROR|> config file: gui_libraries element 'key' is a number, must be string (" << file_path << ")" << std::endl;
            continue;
        }

        if (!element["resolution"]["width"].is_number_integer()) {
            std::cerr << "ERROR|> config file: gui_libraries element 'width' in 'resolution' must be integer (" << file_path << ")" << std::endl;
            continue;
        }

        if (!element["resolution"]["height"].is_number_integer()) {
            std::cerr << "ERROR|> config file: gui_libraries element 'width' in 'resolution' must be integer (" << file_path << ")" << std::endl;
            continue;
        }

        if (element["resolution"]["width"] <= min_resolution_px
            || element["resolution"]["height"] <= min_resolution_px) {
            std::cerr << "ERROR|> config file: resolution width and height must be >= " << min_resolution_px << " (" << file_path << ")" << std::endl;
            continue;
        }

        ConfigLibrary lib;
        lib.key = std::string(element["key"]);
        lib.name = std::string(element["name"]);
        lib.path = std::string(element["path"]);
        lib.resolution_height = element["resolution"]["height"];
        lib.resolution_width = element["resolution"]["width"];
        if (element.contains("font_path")) {
            lib.font_path = std::string(element["font_path"]);
            if (!std::filesystem::exists(lib.font_path)) {
                std::cerr << "ERROR|> Font file does not exist: " << lib.font_path << std::endl;
                continue;
            }
        }

        config.gui_libraries.push_back(lib);
    }

    return config;
}

}
