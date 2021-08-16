#ifndef VIDEOPIPELINE_H
#define VIDEOPIPELINE_H

#include <gst/app/app.h>
#include <gst/app/gstappsink.h>
#include <gst/gst.h>
#include <gst/gstbuffer.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>


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
    appsink

 ****************************************************************************************/

typedef void (*tExtract_Data)(GstMapInfo map, const int width, const int height);

typedef struct
{
    GstElement* pipe;
    GstElement* udpsrc;
    GstElement* src_filter;
    GstElement* rtph264depay;
    GstElement* depay_queue;
    GstElement* decodebin;
    GstElement* decode_queue;
    GstElement* videoconvert;
    GstElement* convert_queue;
    GstElement* sink_filter;
    GstElement* sink_queue;
    GstElement* appsink;
    tExtract_Data Extract_Data;
} tVideoPipeline;

class VideoPipeline {

public:
    VideoPipeline() = default;
    ~VideoPipeline() = default;
    int32_t Construct_Pipeline();

    int32_t Destroy_Pipeline();
    int32_t Set_Pipeline_State_Playing();

    int32_t port;
    tVideoPipeline* pipeline;

private:
    int32_t Create_Elements();
    int32_t Configure_Elements();
    int32_t Link_Elements();
};

#endif /* VIDEOPIPELINE_H */