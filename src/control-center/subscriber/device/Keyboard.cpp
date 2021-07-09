#include "Keyboard.h"

using namespace std;

Keyboard::Keyboard() { }

Keyboard::~Keyboard() { }

int32_t Keyboard::Initialize_Device()
{
    char name[256] = "Unknown";
    if ((file_descriptor = open(device_path, O_RDONLY)) < 0) {
        fprintf(stderr, "[E] [ Control-Center -> Keyboard ] Cannot open %s: %s.\n", device_path, strerror(errno));
        return -1;
    } else {
        printf("[I] [ Control-Center -> Keyboard ] Device Recognized\n");
        ioctl(file_descriptor, JSIOCGNAME(sizeof(name)), name);
        printf("[I] [ Control-Center -> Keyboard ] Device name: %s\n", name);
    }
    return 0;
}

void Keyboard::Process_Input()
{
    while (1) {
        int32_t rd;
        struct input_event ev[64];
        rd = read(file_descriptor, ev, sizeof(struct input_event) * 64);
        if (rd < (int)sizeof(struct input_event)) {
            continue; // If events are being read
        }

        std::lock_guard<std::mutex> lock(mutex);
        for (int32_t i = 0; i < rd / sizeof(struct input_event); i++) {
            if (ev[i].type == EV_KEY) {
                //Steering right
                if (ev[i].code == KEY_RIGHT) {
                    if (PRESSED) {

                    }

                    else {
                    }

                }
                //Steering left
                else if (ev[i].code == KEY_LEFT) {
                    if (PRESSED) {

                    }

                    else {
                    }

                }
                //Acceleration pedal
                else if (ev[i].code == KEY_UP) {
                    if (PRESSED) {

                    } else {
                    }
                }
                //Brake pedal
                else if (ev[i].code == KEY_DOWN) {
                    if (PRESSED) {

                    } else {
                    }

                } else if (ev[i].code == KEY_V) {

                }

                else if (ev[i].code == KEY_C) {
                }
            }
            //Let other threads do their work
            usleep(sleep_timer);
        }
    }
}

void Keyboard::Start_Thread()
{
    input_thread = thread(&Keyboard::Process_Input, this);
    std::cout << "[I] [ Control-Center -> Keyboard ] Keyboard Thread Started" << std::endl;
}
