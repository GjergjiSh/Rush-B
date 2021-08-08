#ifndef RCONFIGURATOR_H
#define RCONFIGURATOR_H

#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

#define TCP_TRANSPORT 0
#define CAMERA 1
#define VIDEO_HOST 2
#define VIDEO_PORT 3
#define SERIAL_PORT 4

#define CLOG_INFO(msg) \
    std::cout << "[I] [ Rush-B : Configurator ] " << msg << std::endl;
#define CLOG_WARNING(msg) \
    std::cerr << "[W] [ Rush-B : Configurator ] " << msg << std::endl;
#define CLOG_ERROR(msg, err) \
    std::cerr << "[E] [ Rush-B : Configurator ] " << msg << " " << err << std::endl;

class Configurator {

public:
    Configurator(const char* config_path);
    std::unordered_map<int, std::string> config_items;
    const char* config_path;

private:
    int32_t Load_Config();
    void Parse_Config();
    void Print_Config();
    pugi::xml_document config;
};

#endif /* RCONFIGURATOR_H */