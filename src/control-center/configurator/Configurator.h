#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <unordered_map>

#define DEVICE 0
#define DEVICE_PATH 1
#define TCP_TRANSPORT 2
#define PY_INTERFACE_ACTIVE 3
#define INTERFACE_TRANSPORT 4
#define VIDEO_PORT 5

#define CLOG_INFO(msg) \
    std::cout << "[I] [ ControlCenter : Configurator ] " << msg << std::endl;
#define CLOG_WARNING(msg) \
    std::cerr << "[W] [ ControlCenter : Configurator ] " << msg << std::endl;
#define CLOG_ERROR(msg, err) \
    std::cerr << "[E] [ ControlCenter : Configurator ] " << msg << " " << err << std::endl;

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

#endif /* CONFIGURATOR_H */