#include "nibbler.hpp"
#include "nibbler/graphics_api.hpp"
#include "snake.hpp"
#include "snake_game.hpp"

#include <memory>
#include <iostream>
#include <dlfcn.h>

namespace nibbler {

Nibbler::Nibbler(Configuration config) : config_(config) { }

int Nibbler::start() {

    if (this->config_.gui_libraries.size() == 0) {
        std::cerr << "ERROR: no libraries in config file" << std::endl;
        return 1;
    }

    std::vector<std::unique_ptr<DynamicLib>> libs;
    std::map<Key, GraphicsApiSharedPtr> gui_instances;
    for (const auto &lib_config : this->config_.gui_libraries)
    {
        std::cout << "Loading " << lib_config.name << ", key: " << lib_config.key << std::endl;

        Key key;
        if (lib_config.key == "0")
            key = Key::NUMBER_0;
        else if (lib_config.key == "1")
            key = Key::NUMBER_1;
        else if (lib_config.key == "2")
            key = Key::NUMBER_2;
        else if (lib_config.key == "3")
            key = Key::NUMBER_3;
        else if (lib_config.key == "4")
            key = Key::NUMBER_4;
        else if (lib_config.key == "5")
            key = Key::NUMBER_5;
        else if (lib_config.key == "6")
            key = Key::NUMBER_6;
        else if (lib_config.key == "7")
            key = Key::NUMBER_7;
        else if (lib_config.key == "8")
            key = Key::NUMBER_8;
        else if (lib_config.key == "9")
            key = Key::NUMBER_9;
        else
        {
            std::cerr << "ERROR: invalid key \"" << lib_config.key << "\" for GUI \"" << lib_config.name << "\"" << std::endl;
            return 1;
        }

        std::unique_ptr<DynamicLib> lib = DynamicLibLoader::load_library(lib_config.path, RTLD_NOW);
        if (lib == nullptr) {
            std::cerr << "ERROR: Cannot load library:" << lib_config.name << std::endl;
            return 1;
        }

        INibblerGraphicsApiConstructor gui_api_constructor = reinterpret_cast<INibblerGraphicsApiConstructor>(lib->get_symbol("create_graphics_library"));
        if (gui_api_constructor == NULL) {
            std::cerr << "ERROR: Cannot load create_graphics_library symbol" << std::endl;
            return 1;
        }
        INibblerGraphicsApiDestructor gui_api_destructor = reinterpret_cast<INibblerGraphicsApiDestructor>(lib->get_symbol("destroy_graphics_library"));
        if (gui_api_destructor == NULL) {
            std::cerr << "ERROR: Cannot load destroy_graphics_library symbol" << std::endl;
            return 1;
        }

        GraphicsApiSharedPtr graphics_api(gui_api_constructor(), gui_api_destructor);
        gui_instances.insert(std::make_pair(key, graphics_api));

        libs.push_back(std::move(lib)); // store the libs to avoid them being destroyed every turn of the loop
    }

    SnakeGame game(this->config_, gui_instances);
    return game.run();
}

}