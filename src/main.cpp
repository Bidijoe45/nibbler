#include <iostream>
#include <string>

#include "nibbler.hpp"
#include "config.hpp"

int main() {
    std::string config_file("./nibbler-config.json");
    nibbler::Configuration config = nibbler::ConfigParser::parseConfigFile(config_file);    
    nibbler::Nibbler nibbler;
    
    nibbler.run();
}