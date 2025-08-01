#include <iostream>
#include <string>

//#include "clipp.h"

#include "nibbler.hpp"
#include "config.hpp"

int main(int argc, char **argv) {
    size_t widthArg, heightArg = 0;
    std::string config_file;

    /*auto cli = (
        clipp::required("-w").doc("Set the window width") & clipp::value("width", widthArg),
        clipp::required("-h").doc("Set the window width") & clipp::value("height", heightArg),
        clipp::option("-f").doc("Specify configuration file") & clipp::value("config file path", config_file)
    );

    if(!clipp::parse(argc, argv, cli)) {
        std::cout << clipp::make_man_page(cli, argv[0]);
        return 1;
    }*/

    if (config_file.size() == 0)
        config_file = "./nibbler-config.json";

    nibbler::Configuration config = nibbler::ConfigParser::parseConfigFile(config_file);
    nibbler::Nibbler nibbler(config);
    
    return nibbler.start();
}