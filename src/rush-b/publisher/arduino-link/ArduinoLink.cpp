#include "ArduinoLink.h"

ArduinoLink::ArduinoLink(){};
ArduinoLink::~ArduinoLink(){};

int32_t ArduinoLink::Init_Serial_Port(std::string port)
{
    try {
        this->serial_port = new SerialPort(port, BaudRate::B_460800);
        this->serial_port->SetTimeout(-1);
        this->serial_port->Open();
        std::cout << "[I] [ Rush-B -> ArduinoLink] Arduino board connected on port: " << port << std::endl;
    } catch (mn::CppLinuxSerial::Exception& ex) {
        std::cerr << "[E] [ Rush-B -> ArduinoLink ] Connection to Arduino failed to initialize." << ex.what() << std::endl;
        return -1;
    }
    return 0;
}

int32_t ArduinoLink::Deinit_Serial_Port()
{
    try {
        this->serial_port->Close();
        std::cout << "[I] [ Rush-B -> ArduinoLink] Connection to Arduino deinitialized " << std::endl;
    } catch (mn::CppLinuxSerial::Exception& ex) {
        std::cerr << "[E] [ Rush-B -> ArduinoLink ] Connection to Arduino failed to deinitialize." << ex.what() << std::endl;
        return -1;
    }
    return 0;
}

int32_t ArduinoLink::Write_To_Port(PBDriverWish::PBDriverWish driver_wish)
{
    try {
        //driver_wish = !left%right#top&\n
        std::string left_servo = std::to_string(driver_wish.left_servo()) + "%";
        std::string right_servo = std::to_string(driver_wish.right_servo()) + "#";
        std::string top_servo = std::to_string(driver_wish.top_servo()) + "&";
        std::string s_driver_wish = left_servo + right_servo + top_servo;

        //std::cout << s_driver_wish << std::endl;
        this->serial_port->Write("!" + s_driver_wish + "\n");

    } catch (mn::CppLinuxSerial::Exception& ex) {
        std::cerr << "[E] [ Rush-B -> ArduinoLink ] Failed to write driver wishes to the robot." << ex.what() << std::endl;
        return -1;
    }
    return 0;
}