#include "Keyboard.h"

Keyboard::Keyboard()
{
    this->driver_wish.set_left_servo(90);
    this->driver_wish.set_right_servo(90);
    this->driver_wish.set_top_servo(0);
}

int32_t Keyboard::Initialize_Device(const char* device_path)
{
    this->device_path = device_path;
    char name[256] = "Unknown";
    if ((file_descriptor = open(device_path, O_RDONLY)) < 0) {
        fprintf(stderr, "[E] [ Device : Keyboard ] Cannot open %s: %s.\n", this->device_path, strerror(errno));
        return -1;
    } else {
        printf("[I] [ Device : Keyboard ] Device Recognized\n");
        ioctl(file_descriptor, JSIOCGNAME(sizeof(name)), name);
        printf("[I] [ Device : Keyboard ] Device name: %s\n", name);
    }
    return 0;
}

int32_t Keyboard::Process_Input()
{
    int32_t rd;
    struct input_event ev[64];
    rd = read(file_descriptor, ev, sizeof(struct input_event) * 64);
    if (rd > (int)sizeof(struct input_event)) {
        for (long unsigned int i = 0; i < rd / sizeof(struct input_event); i++) {
            if (ev[i].type == EV_KEY) {
                if (ev[i].code == KEY_RIGHT && PRESSED) { Turn_Right(); }
                else if (ev[i].code == KEY_LEFT && PRESSED) { Turn_Left(); }
                else if (ev[i].code == KEY_UP && PRESSED) { Go_Forward(); }
                else if (ev[i].code == KEY_DOWN && PRESSED) { Go_Backwards(); }
                else if (ev[i].code == KEY_V && PRESSED) { }
                else if (ev[i].code == KEY_C && PRESSED) { }
                else if (ev[i].code == KEY_SPACE && PRESSED) { Full_Stop(); }
            }
        }
    } else {
        return -1;
    }
    return 0;
}

void Keyboard::Turn_Left()
{
    if (this->driver_wish.left_servo() != 0) {
        this->driver_wish.set_left_servo(this->driver_wish.left_servo() - VAL);
    }
    if (this->driver_wish.right_servo() !=180) {
        this->driver_wish.set_right_servo(this->driver_wish.right_servo() + VAL);
    }
}

void Keyboard::Turn_Right()
{
    if (this->driver_wish.right_servo() != 0) {
        this->driver_wish.set_right_servo(this->driver_wish.right_servo() - VAL);
    }
    if (this->driver_wish.left_servo() != 180) {
        this->driver_wish.set_left_servo(this->driver_wish.right_servo() + VAL);
    }
}

void Keyboard::Go_Forward()
{
    if (this->driver_wish.right_servo() != 180 && this->driver_wish.left_servo() != 180) {
        this->driver_wish.set_right_servo(this->driver_wish.right_servo() + VAL);
        this->driver_wish.set_left_servo(this->driver_wish.left_servo() + VAL);
    }
}

void Keyboard::Go_Backwards()
{
    if (this->driver_wish.right_servo() != 0 && this->driver_wish.left_servo() != 0) {
        this->driver_wish.set_right_servo(this->driver_wish.right_servo() - VAL);
        this->driver_wish.set_left_servo(this->driver_wish.left_servo() - VAL);
    }
}

void Keyboard::Full_Stop()
{
    this->driver_wish.set_right_servo(90);
    this->driver_wish.set_left_servo(90);
}

void Keyboard::Print_Driver_Wish()
{
    std::cout << "Top-Servo: " << driver_wish.top_servo() << std::endl;
    std::cout << "Left-Servo: " << driver_wish.left_servo() << std::endl;
    std::cout << "Right-Servo: " << driver_wish.right_servo() << std::endl;
}
