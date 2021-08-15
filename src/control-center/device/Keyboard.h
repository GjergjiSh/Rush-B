#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Device.h"

#define PRESSED ((ev[i].value == 1 || ev[i].value == 2))
#define VAL 10

class Keyboard : public Device {
public:
    Keyboard();
    ~Keyboard() = default;
    int32_t Initialize_Device(const char* device_path) override;
    int32_t Process_Input() override;
    void Print_Driver_Wish() override;

private:
    void Turn_Left();
    void Turn_Right();
    void Go_Forward();
    void Go_Backwards();
    void Full_Stop();
};

#endif /* KEYBOARD_H */
