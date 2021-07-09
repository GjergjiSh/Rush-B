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
    ~Controller();

    bool Connected();
    size_t Moved_Stick();
    void Handle_Button_Events();
    void Handle_Thumbstick_Events();
    void Process_Input();
    void Start_Thread();
    int32_t Initialize_Device();

    coordinates stick_coordinates[3];
    js_event event;

private:
};

#endif /* CONTROLLER_H */
