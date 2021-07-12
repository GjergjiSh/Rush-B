#include "RushB.h"

RushB::RushB() {};
RushB::~RushB() {};

int32_t RushB::Init()
{
    this->subscriber = new Subscriber();
    this->publisher = new Publisher();

    //TODO:Temporarily hardcoded, needs to be read from cfg
    this->subscriber->zqm_sub_transport = "127.0.0.1:5001";
    int zmq_status = this->subscriber->ZMQ_Init_Connection();
    int video_status = this->publisher->Start_Publishing_Video();
    if (zmq_status + video_status == 0)
    {
        std::cout << "[I] [ Rush-B -> Init ] Rush-B Successfuly Initialized " << std::endl;
    }
    else
    {
        std::cerr << "[E] [ Rush-B -> Init ] Rush-B Failed to Initialize " << std::endl;
    }
    return zmq_status;
}

int32_t RushB::Control_Robot()
{
    PBDriverWish::PBDriverWish driver_wish = this->subscriber->ZMQ_Receive();

    //Currently only printing out for testing purpouses
    // std::cout << "Top-Servo:" << driver_wish.top_servo() << std::endl;
    // std::cout << "Left-Servo:" << driver_wish.left_servo() << std::endl;
    // std::cout << "Right-Servo:" << driver_wish.right_servo() << std::endl;

    return 0;
}

int32_t RushB::Deinit()
{
    int zmq_status = this->subscriber->ZMQ_Deinit_Connection();
    int video_status = this->publisher->video_publisher.Destroy_Pipeline();

    if (zmq_status + video_status == 0) {
        std::cout << "[I] [ Rush-B -> Deinit ] Rush-B Successfuly Deinitialized " << std::endl;

    } else {
        std::cerr << "[E] [ Rush-B -> Deinit ] Rush-B Failed to Deinitialize " << std::endl;
    }

    delete this->subscriber;
    delete this->publisher;
    return zmq_status + video_status;
}