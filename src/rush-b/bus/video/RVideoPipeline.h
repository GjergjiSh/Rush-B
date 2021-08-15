#ifndef R_VIDEOPIPELINE_H
#define R_VIDEOPIPELINE_H

#include <gst/gst.h>
#include <iostream>
#include <memory>
#include <string.h>
#include <unordered_map>

typedef struct
{
    GstElement* pipe;
    GstElement* v4l2src;
    GstElement* videoconvert;
    GstElement* x264enc;
    GstElement* rtph264pay;
    GstElement* udpsink;
} tVideoPipeline;

class VideoPipeline {

public:
    VideoPipeline() = default;
    ~VideoPipeline() = default;
    int32_t Construct_Pipeline();
    int32_t Destroy_Pipeline();
    int32_t Set_Pipeline_State_Playing();

    std::shared_ptr<tVideoPipeline> pipeline;
    std::string camera;
    std::string camera_subscriber_host;
    int camera_subscriber_port;

private:
    int32_t Create_Elements();
    int32_t Configure_Elements();
    int32_t Link_Elements();
};

#endif /* R_VIDEOPIPELINE_H */