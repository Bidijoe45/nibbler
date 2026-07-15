#include <iostream>
#include <string>

#include "clipp.h"

#include "nibbler.hpp"
#include "config.hpp"

int main(int argc, char **argv) {
    int32_t game_width_squares, game_height_squares = 0;
    std::string config_file_path = "./config/nibbler-config.json";
    std::vector<std::string> wrong_args;

    auto cli = (
        clipp::required("-w").doc("Set the game area's width (measured in squares)") & clipp::number("width", game_width_squares),
        clipp::required("-h").doc("Set the game area's height (measured in squares)") & clipp::number("height", game_height_squares),
        clipp::option("-f").doc("Path to the json configuration file") & clipp::value("config_file_path", config_file_path),
        clipp::any_other(wrong_args)
    );

    auto res = clipp::parse(argc, argv, cli);
    if (res.any_error() || !wrong_args.empty())
    {
        for (const auto &arg : wrong_args) 
            std::cout << "Invalid argument: '" << arg << "'" << std::endl;
        for (const auto &m : res.missing()) {
            if (!m.param()->label().empty())
                std::cout << "Missing argument: " << m.param()->label() << std::endl;
        }
        std::cout << clipp::make_man_page(cli, argv[0]);
        return 1;
    }

    constexpr int32_t min_squares = 8;
    constexpr int32_t max_squares = 200;
    if (game_height_squares < min_squares || game_width_squares < min_squares) {
        std::cerr << "ERROR | arguments: width and height must be >= " << min_squares << std::endl;
        return 1;
    }

    if (game_height_squares > max_squares || game_width_squares > max_squares) {
        std::cerr << "ERROR | arguments: width and height must be <= " << max_squares << std::endl;
        return 1;
    }

    nibbler::Configuration config = nibbler::ConfigParser::parseConfigFile(config_file_path);
    config.gameboard_width_squares = game_width_squares;
    config.gameboard_height_squares = game_height_squares;

    nibbler::Nibbler nibbler(config);
    
    return nibbler.start();
}