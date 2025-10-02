#include "config.hpp"

#include "nlohmann/json.hpp"

#include <string>
#include <fstream>
#include <iostream>

namespace nibbler {

Configuration ConfigParser::parseConfigFile(const std::string &file_path) {
    Configuration config;

    std::ifstream file(file_path);
    nlohmann::json data = nlohmann::json::parse(file);

    if (!data.contains("gui_libraries")) {
        std::cout << "ERROR: missing property gui_libraries in " << file_path << std::endl;
        return config;
    }

    for (auto& element : data["gui_libraries"]) {
        if (!element.contains("key")) {
            std::cout << "ERROR: gui_libraries element missing 'key' property in " << file_path << std::endl;
            return config;
        }
        else if (!element.contains("name")) {
            std::cout << "ERROR: gui_libraries element missing 'name' property in " << file_path << std::endl;
            return config;
        }
        else if (!element.contains("path")) {
            std::cout << "ERROR: gui_libraries element missing 'path' property in " << file_path << std::endl;
            return config;
        }

        if (element["key"].is_number()) {
            std::cout << "ERROR: gui_libraries element 'key' is a number, must be string " << file_path << std::endl;
            return config;
        }

        ConfigLibrary lib;
        lib.key = std::string(element["key"]);
        lib.name = std::string(element["name"]); 
        lib.path = std::string(element["path"]);

        config.gui_libraries.push_back(lib);
    }

    return config;
}

}
