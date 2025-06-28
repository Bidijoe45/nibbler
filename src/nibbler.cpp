#include "nibbler.hpp"
#include "nibbler/graphics_api.hpp"
#include <snake.hpp>

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

    ConfigLibrary first_library = this->config_.gui_libraries.at(0);
    std::unique_ptr<DynamicLib> gui_lib = DynamicLibLoader::load_library(first_library.path, RTLD_LAZY);

    if (gui_lib == nullptr) {
        std::cerr << "ERROR: Cannot load library:" << first_library.name << std::endl;
        return 1;
    }

    INibblerGraphicsApiConstructor create_gui_lib = reinterpret_cast<INibblerGraphicsApiConstructor>(gui_lib->get_symbol("create_graphics_library"));
    INibblerGraphicsApiDestructor destroy_gui_lib
        = reinterpret_cast<INibblerGraphicsApiDestructor>(gui_lib->get_symbol("destroy_graphics_library"));

    if (create_gui_lib == NULL) {
        std::cerr << "ERROR: Cannot load create_graphics_library symbol" << std::endl;
        return 1;
    }

    if (destroy_gui_lib == NULL) {
        std::cerr << "ERROR: Cannot load destroy_graphics_library symbol" << std::endl;
        return 1;
    }

    GraphicsApiUniquePtr graphics_api(create_gui_lib(), destroy_gui_lib);
    Snake snake(this->config_, std::move(graphics_api));

    return snake.run();
}

}