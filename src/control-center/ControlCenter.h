#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include "Controller.h"
#include "Keyboard.h"
#include "Bus.h"

#define CONTROLLER 1
#define KEYBOARD 2

class ControlCenter {

public:
    ControlCenter() = default;
    ~ControlCenter() = default;

    int32_t Connect_Device();

    int32_t Init();
    int32_t Control_Robot();
    int32_t Deinit();

    int32_t active_device;

    Keyboard keyboard;
    Controller controller;
    Bus bus;

};

#endif /* CONTROLCENTER_H */