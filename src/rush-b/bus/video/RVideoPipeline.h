#ifndef R_VIDEOPIPELINE_H
#define R_VIDEOPIPELINE_H

#include <gst/gst.h>
#include <iostream>
#include <string.h>
#include <unordered_map>

typedef struct
{
    int tune;
    int speed_preset;
    int bitrate;
} tX264Param;

typedef struct
{
    std::string host;
    int port;
} tSINKParam;

typedef struct
{
    std::string camera;
    tX264Param x264_param;
    tSINKParam sink_param;
} tVideoPipelineParam;

typedef struct
{
    GstElement* pipe;
    GstElement* v4l2src;
    GstElement* videoconvert;
    GstElement* x264enc;
    GstElement* rtph264pay;
    GstElement* udpsink;
    tVideoPipelineParam parameters;
} tVideoPipeline;

class VideoPipeline {

public:
    VideoPipeline() = default;
    ~VideoPipeline() = default;
    int32_t Construct_Pipeline();
    int32_t Create_Elements();
    int32_t Configure_Elements();
    int32_t Link_Elements();
    int32_t Destroy_Pipeline();
    int32_t Set_Pipeline_State_Playing();

    tVideoPipelineParam* pipeline_parameters;
    tVideoPipeline* pipeline;
};

#endif /* R_VIDEOPIPELINE_H */