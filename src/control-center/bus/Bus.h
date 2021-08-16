#ifndef BUS_H
#define BUS_H

#include "PBDriverWish.pb.h"
#include "TFLiteDetector.h"
#include "VideoPipeline.h"
#include "ZMQPipeline.h"
#include <mutex>
#include <thread>

#define LOG_INFO(msg) \
    std::cout << "[I] [ ControlCenter : Bus ] " << msg << std::endl;
#define LOG_WARNING(msg) \
    std::cerr << "[W] [ ControlCenter : Bus ] " << msg << std::endl;
#define LOG_ERROR(msg, err) \
    std::cerr << "[E] [ ControlCenter : Bus ] " << msg << " " << err << std::endl;


class Bus {
public:
    Bus() = default;
    ~Bus() = default;
    int32_t Init();
    int32_t Deinit();

    int32_t ZMQ_Init_Pipeline();
    int32_t ZMQ_Deinit_Pipeline();
    int32_t Publish_Driver_Wish(const std::string topic, std::string data);
    std::string Receive_PyDriverWish();

    int32_t Video_Init_Pipeline();
    int32_t Video_Deinit_Pipeline();
    void Init_Object_Detector();
    void Invoke_Detector();
    void Display_Video();

    ZMQPipeline zmq_pipeline;

    VideoPipeline video_sub_pipe;
    std::mutex v_mutex;
    cv::Mat last_appsink_frame;

    TFLiteDetector object_detector;
    std::mutex p_mutex;
    std::thread detection_thread;
    std::vector<tBoundingBox> detection_results;
    bool object_detection_active = false;
};

#endif /* BUS_H */