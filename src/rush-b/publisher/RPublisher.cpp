#include "RPublisher.h"

Publisher::Publisher(){};
Publisher::~Publisher(){};

int32_t Publisher::Start_Publishing_Video()
{
    {//TODO: This scope is hardcoded and needs to be read from config in the future
        this->video_publisher.pipeline.parameters.camera = "/dev/video0";
        this->video_publisher.pipeline.parameters.x264_param.speed_preset = 1;
        this->video_publisher.pipeline.parameters.x264_param.bitrate = 2000;
        this->video_publisher.pipeline.parameters.x264_param.tune = 0x00000004;
        this->video_publisher.pipeline.parameters.sink_param.host = "127.0.0.1";
        this->video_publisher.pipeline.parameters.sink_param.port = 5000;
    }

    if (this->video_publisher.Construct_Pipeline("RushB Video Pipeline", &this->video_publisher.pipeline) == 0) {
        int32_t pipeline_status = this->video_publisher.Set_Pipeline_State_Playing();
        return pipeline_status;
    }
    return -1;
}

int32_t Publisher::Stop_Publishing_Video()
{
    int32_t video_status = this->video_publisher.Destroy_Pipeline();
    return video_status;
}