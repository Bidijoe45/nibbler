#include <iostream>
#include <string>

#include "clipp.h"

#include "nibbler.hpp"
#include "config.hpp"

int main(int argc, char **argv) {
    size_t game_width_squares, game_height_squares = 0;
    std::string config_file_path = "./nibbler-config.json";

    auto cli = (
        clipp::required("-w").doc("Set the game area's width (measured in squares)") & clipp::value("width", game_width_squares),
        clipp::required("-h").doc("Set the game area's height (measured in squares)") & clipp::value("height", game_height_squares),
        clipp::option("-f").doc("Path to the json configuration file") & clipp::value("config_file_path", config_file_path)
    );

    if (!clipp::parse(argc, argv, cli))
    {
        std::cout << clipp::make_man_page(cli, argv[0]);
        return 1;
    }

    nibbler::Configuration config = nibbler::ConfigParser::parseConfigFile(config_file_path);
    config.gameboard_width_squares = game_width_squares;
    config.gameboard_height_squares = game_height_squares;

    nibbler::Nibbler nibbler(config);
    
    return nibbler.start();
}