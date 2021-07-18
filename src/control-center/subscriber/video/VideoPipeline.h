#ifndef VIDEOPIPELINE_H
#define VIDEOPIPELINE_H

#include <gst/gst.h>
#include <iostream>
#include <string>
#include <thread>

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

class VideoSubscriber {

public:
    VideoSubscriber();
    ~VideoSubscriber();
    int32_t Construct_Pipeline();
    int32_t Create_Elements();
    int32_t Configure_Elements();
    int32_t Link_Elements();
    int32_t Destroy_Pipeline();
    int32_t Set_Pipeline_State_Playing();
    void Start_Gloop();

    int32_t port;
    tVideoPipeline* pipeline;
    GMainLoop* loop;
};

#endif /* VIDEOPIPELINE_H */