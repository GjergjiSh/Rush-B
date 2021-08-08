#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Device.h"

#define LEFTSTICK 0
#define RIGHTSTICK 2
#define L1 4
#define R1 5
#define SELECT 6
#define START 7
#define L3 9
#define R3 10

struct coordinates {
    _Float64 x, y;
};

class Controller : public Device {
public:
    Controller();
    ~Controller() = default;

    int32_t Process_Input() override;
    int32_t Initialize_Device(const char* device_path) override;
    void Print_Driver_Wish() override;

private:
    void Handle_Button_Events();
    void Handle_Thumbstick_Events();
    bool Connected();

    coordinates stick_coordinates[3];
    js_event event;
    size_t Moved_Stick();
};

#endif /* CONTROLLER_H */
