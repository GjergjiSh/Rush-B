#ifndef _ARDUINO_LINK_H
#define _ARDUINO_LINK_H

#include "PBDriverWish.pb.h"
#include <CppLinuxSerial/Exception.hpp>
#include <CppLinuxSerial/SerialPort.hpp>
#include <string>

#define ALOG_INFO(msg) \
    std::cout << "[I] [ Bus : Arduino-Link ] " << msg << std::endl;
#define ALOG_WARNING(msg) \
    std::cerr << "[W] [ Bus : Arduino-Link ] " << msg << std::endl;
#define ALOG_ERROR(msg, err) \
    std::cerr << "[E] [ Bus : Arduino-Link ] " << msg << " " << err << std::endl;

using namespace mn::CppLinuxSerial;

class ArduinoLink
{

public:
    ArduinoLink();
    ~ArduinoLink();

    int32_t Init_Serial_Port(std::string port);
    int32_t Deinit_Serial_Port();
    int32_t Write_To_Port(PBDriverWish::PBDriverWish driver_wish);

    SerialPort* serial_port;
    std::string port;
};

#endif /* _ARDUINO_LINK_H */