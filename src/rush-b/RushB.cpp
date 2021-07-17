#include "RushB.h"

RushB::RushB() {};
RushB::~RushB() {};

int32_t RushB::Init()
{
    this->subscriber = new Subscriber();
    this->publisher = new Publisher();

    {//TODO:Temporarily hardcoded, needs to be read from cfg
    this->subscriber->zqm_sub_transport = "127.0.0.1:5001";
    //this->publisher->arduino_link.port = "/dev/ttyACM0";
    }

    int32_t zmq_status = this->subscriber->ZMQ_Init_Connection();
    int32_t video_status = this->publisher->Start_Publishing_Video();
    int32_t arduino_status = this->publisher->arduino_link.Init_Serial_Port("/dev/ttyACM0");
    //int32_t arduino_status = 0;

    if (zmq_status + video_status + arduino_status == 0)
    {
        std::cout << "[I] [ Rush-B -> Init ] Rush-B Successfuly Initialized " << std::endl;
    }
    else
    {
        std::cerr << "[E] [ Rush-B -> Init ] Rush-B Failed to Initialize " << std::endl;
    }
    return zmq_status + video_status + arduino_status;
}

int32_t RushB::Control_Robot()
{
    PBDriverWish::PBDriverWish driver_wish = this->subscriber->ZMQ_Receive();
    //int32_t status = this->publisher->arduino_link.Write_To_Port(driver_wish);

    //Currently only printing out for testing purpouses
    std::cout << "Top-Servo:" << driver_wish.top_servo() << std::endl;
    std::cout << "Left-Servo:" << driver_wish.left_servo() << std::endl;
    std::cout << "Right-Servo:" << driver_wish.right_servo() << std::endl;

    return 0;
}

int32_t RushB::Deinit()
{
    int32_t zmq_status = this->subscriber->ZMQ_Deinit_Connection();
    int32_t video_status = this->publisher->video_publisher.Destroy_Pipeline();
    //int32_t arduino_status = this->publisher->arduino_link.Deinit_Serial_Port();
    int32_t arduino_status = 0;

    if (zmq_status + video_status + arduino_status == 0) {
        std::cout << "[I] [ Rush-B -> Deinit ] Rush-B Successfuly Deinitialized " << std::endl;

    } else {
        std::cerr << "[E] [ Rush-B -> Deinit ] Rush-B Failed to Deinitialize " << std::endl;
    }

    delete this->subscriber;
    delete this->publisher;
    delete this;
    return zmq_status + video_status +arduino_status;
}