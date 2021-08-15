#ifndef VIDEOPIPELINE_H
#define VIDEOPIPELINE_H

#include <gst/gst.h>
#include <iostream>
#include <string>
#include <thread>

#define VLOG_INFO(msg) \
    std::cout << "[I] [ Bus : VideoPipeline  ] " << msg << std::endl;
#define VLOG_WARNING(msg) \
    std::cerr << "[W] [ Bus : VideoPipeline ] " << msg << std::endl;
#define VLOG_ERROR(msg, err) \
    std::cerr << "[E] [ Bus : VideoPipeline  ] " << msg << " " << err << std::endl;

/**************************************    Pipeline    *********************************

    gst-launch-1.0 -v udpsrc port=xxxx ! \
   "application/x-rtp, media=video, clock-rate=90000, encoding-name=H264, payload=96" ! \
    rtph264depay ! \
    decodebin ! \
    videoconvert ! \
    queue ! \
    autovideosink

 ****************************************************************************************/

typedef struct
{
    GstElement* pipe;
    GstElement* udpsrc;
    GstElement* filter;
    GstElement* rtph264depay;
    GstElement* decodebin;
    GstElement* videoconvert;
    GstElement* queue;
    GstElement* autovideosink;
} tVideoPipeline;

class VideoPipeline {

public:
    VideoPipeline() = default;
    ~VideoPipeline() = default;
    int32_t Construct_Pipeline();

    int32_t Destroy_Pipeline();
    int32_t Set_Pipeline_State_Playing();
    void Start_Gloop();

    int32_t port;
    std::shared_ptr<tVideoPipeline> pipeline;
    GMainLoop* loop;
    std::thread video_thread;

private:
    int32_t Create_Elements();
    int32_t Configure_Elements();
    int32_t Link_Elements();
};

#endif /* VIDEOPIPELINE_H */