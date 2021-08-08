#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#define DRAW_LINE                                                                                    \
    std::cout << " ================================================================= " << std::endl; \
    std::cout << " -----------------------|   Control Center  |--------------------- " << std::endl; \
    std::cout << " ================================================================= " << std::endl;

#include "Controller.h"
#include "Keyboard.h"
#include "Bus.h"
#include "Configurator.h"
#include <unordered_map>


#define CONTROLLER 1
#define KEYBOARD 2

class ControlCenter {

public:
    ControlCenter(const char* config_path);
    ~ControlCenter() = default;

    int32_t Init();
    int32_t Control_Robot();
    int32_t Deinit();

private:
    std::string active_device;
    Configurator* configurator;
    Device* device;
    Bus bus;



};

#endif /* CONTROLCENTER_H */