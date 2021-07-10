#include "Controller.h"

using namespace std;

Controller::Controller() { }
Controller::~Controller() { }

/*********************************************************************
 * @brief  Initializes the Controller
 * @return int32_t 0 if successful or -1 if not successful
 *****************************************************************/
int32_t Controller::Initialize_Device()
{
    char name[256] = "Unknown";
    if ((file_descriptor = open(device_path, O_RDONLY)) < 0) {
        fprintf(stderr, "[E] [ Control-Center -> Controller ] Cannot open %s: %s.\n", device_path, strerror(errno));
        return -1;
    } else {
        printf("[I] [ Control-Center -> Controller ] Device Recognized\n");
        ioctl(file_descriptor, JSIOCGNAME(sizeof(name)), name);
        printf("[I] [ Control-Center -> Controller ] Device name: %s\n", name);
    }
    return 0;
}

/********************************************************************
     * @brief Checks if the device is Connected
     * @return TRUE if the Device is Connected and FALSE if it is not
     ****************************************************************/
bool Controller::Connected()
{
    js_event* ev = &event;
    ssize_t bytes;
    bytes = read(file_descriptor, ev, sizeof(*ev));
    if (bytes == sizeof(*ev)) {
        return true;
    }
    return false;
}

/*********************************************************************
     * @brief Updates the coordinates of the thumbstick that is moved
     * @return The moved thumbstick
     *****************************************************************/
size_t Controller::Moved_Stick()
{
    js_event* ev = &event;
    size_t thumbstick = ev->number / 2;

    if (ev->number % 2 == 0)
        stick_coordinates[thumbstick].x = ev->value;
    else
        stick_coordinates[thumbstick].y = ev->value;

    return thumbstick;
}

/*********************************************************************
     * @brief Update DriverWish actions; Engine on/off, Gearshifts
     ****************************************************************/
void Controller::Handle_Button_Events()
{
    js_event* ev = &event;

    if (ev->number == L1) { //Turn Camera Left
        this->driver_wish.set_top_servo(this->driver_wish.top_servo() - 10);
    }
    else if (ev->number == R1) { //Turn Camera Right
        this->driver_wish.set_top_servo(this->driver_wish.top_servo() + 10);
    }
}

/***************************************************************************
     * @brief Updates the Acceleration, Brake and Steering values
     * @note: The Linux/Joystick API is somewhat counter-intuitive. Positive
     *        coordinates traslate to downwards movement and vice-versa.
     ***********************************************************************/
void Controller::Handle_Thumbstick_Events()
{
    size_t thumb_stick = Moved_Stick();

    if (thumb_stick == RIGHTSTICK) {

        if (stick_coordinates[RIGHTSTICK].x > 0) // Right Thumbstick Moving Down
        {
            this->driver_wish.set_right_servo(stick_coordinates[RIGHTSTICK].x);
        } else if (stick_coordinates[RIGHTSTICK].x < 0) // Right Thumbstick Moving Up
        {
            this->driver_wish.set_right_servo(stick_coordinates[RIGHTSTICK].x);
        } else // Left Thumbstick not moving
        {
            this->driver_wish.set_right_servo((0));
        }
    } else if (thumb_stick == LEFTSTICK) {
        if (stick_coordinates[LEFTSTICK].y > 0) // Left Thumbstick Moving Down
        {
            this->driver_wish.set_left_servo(stick_coordinates[LEFTSTICK].y);

        } else if (stick_coordinates[LEFTSTICK].y < 0) // Left Thumbstick Moving Up
        {
            this->driver_wish.set_left_servo(stick_coordinates[LEFTSTICK].y);
        } else // Left Thumbstick not moving
        {
            this->driver_wish.set_left_servo((0));
        }
    }
}

/********************************************************************************************
     * @brief Listens for events and processes them as long as the Device is connected
     ****************************************************************************************/
void Controller::Process_Input()
{
    while (Connected()) {
        std::lock_guard<std::mutex> lock(mutex);
        switch (event.type) {
        case JS_EVENT_BUTTON:
            Handle_Button_Events();
            break;
        case JS_EVENT_AXIS:
            Handle_Thumbstick_Events();
            break;
        default:
            break;
        }
        usleep(sleep_timer);
    }
}

void Controller::Start_Thread()
{
    input_thread = thread(&Controller::Process_Input, this);
    std::cout << "[I] [ Control-Center  -> Controller ] Controller Thread Started" << std::endl;
}

void Controller::Print_Driver_Wish()
{
    std::cout << "Top-Servo: " << driver_wish.top_servo() << std::endl;
    std::cout << "Left-Servo: " << driver_wish.left_servo() << std::endl;
    std::cout << "Right-Servo: " << driver_wish.right_servo() << std::endl;
}
