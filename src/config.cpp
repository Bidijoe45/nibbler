#include "config.hpp"

#include "nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <iostream>

namespace nibbler {

Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    std::ifstream file(file_path);

    if (!file.good()) {
        std::cout << "ERROR | file does not exist: " << file_path << std::endl;
        return config;
    }

    nlohmann::json data = nlohmann::json::parse(file);

    if (!data.contains("gui_libraries")) {
        std::cout << "ERROR | config file: missing property gui_libraries in " << file_path << std::endl;
        return config;
    }

    for (auto& element : data["gui_libraries"]) {
        if (!element.contains("key")) {
            std::cout << "ERROR|> config file: gui_libraries element missing 'key' property in " << file_path << std::endl;
            return config;
        }
        if (!element.contains("name")) {
            std::cout << "ERROR|> config file: gui_libraries element missing 'name' property in " << file_path << std::endl;
            return config;
        }
        if (!element.contains("path")) {
            std::cout << "ERROR|> config file: gui_libraries element missing 'path' property in " << file_path << std::endl;
            return config;
        }
        if (!element.contains("resolution")) {
            std::cout << "ERROR|> config file: gui_libraries element missing 'resolution' property in " << file_path << std::endl;
            return config;
        }
        if (!element["resolution"].contains("width")) {
            std::cout << "ERROR|> config file: gui_libraries resolution element missing 'width' property in " << file_path << std::endl;
            return config;
        }
        if (!element["resolution"].contains("height")) {
            std::cout << "ERROR|> config file: gui_libraries resolution element missing 'height' property in " << file_path << std::endl;
            return config;
        }

        if (element["key"].is_number()) {
            std::cout << "ERROR|> config file: gui_libraries element 'key' is a number, must be string " << file_path << std::endl;
            return config;
        }

        if (!element["resolution"]["width"].is_number_integer()) {
            std::cout << "ERROR|> config file: gui_libraries element 'width' in 'resolution' must be integer " << file_path << std::endl;
            return config;
        }

        if (!element["resolution"]["height"].is_number_integer()) {
            std::cout << "ERROR|> config file: gui_libraries element 'width' in 'resolution' must be integer " << file_path << std::endl;
            return config;
        }

        // TODO: add these mins (or maxes) should be in some sort of constant, and should be checked when RESIZING the windows too!!
        if (element["resolution"]["width"] <= 63 || element["resolution"]["height"] <= 63) {
            std::cout << "ERROR|> config file: resolution widht or height must be >= 64" << file_path << std::endl;
            return config;
        }

        ConfigLibrary lib;
        lib.key = std::string(element["key"]);
        lib.name = std::string(element["name"]);
        lib.path = std::string(element["path"]);
        lib.resolution_height = element["resolution"]["height"];
        lib.resolution_width = element["resolution"]["width"];
        if (element.contains("font_path"))
            lib.font_path = std::string(element["font_path"]);

        config.gui_libraries.push_back(lib);
    }

    return config;
}

}
