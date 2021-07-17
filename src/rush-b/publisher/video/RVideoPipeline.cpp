#include <RVideoPipeline.h>

VideoPublisher::VideoPublisher() { }
VideoPublisher::~VideoPublisher() { }

int32_t VideoPublisher::Construct_Pipeline(const char* name, tVideoPipeline* const pipeline)
{
    //Init Gstreamer
    gst_init(NULL, NULL);

    //Create Elements
    pipeline->v4l2src = gst_element_factory_make("v4l2src", NULL);
    g_object_set(pipeline->v4l2src, "device", pipeline->parameters.camera.c_str(), NULL);

    pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);

    pipeline->x264enc = gst_element_factory_make("x264enc", NULL);
    g_object_set(pipeline->x264enc, "tune", pipeline->parameters.x264_param.tune, NULL);
    g_object_set(pipeline->x264enc, "speed-preset", pipeline->parameters.x264_param.speed_preset, NULL);
    g_object_set(pipeline->x264enc, "bitrate", pipeline->parameters.x264_param.bitrate, NULL);

    pipeline->rtph264pay = gst_element_factory_make("rtph264pay", NULL);

    pipeline->udpsink = gst_element_factory_make("udpsink", NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "host", pipeline->parameters.sink_param.host.c_str(), NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "port", pipeline->parameters.sink_param.port, NULL);

    //Create Empty Pipeline
    pipeline->pipe = gst_pipeline_new(name);

    if (!pipeline->pipe || !pipeline->v4l2src || !pipeline->videoconvert || !pipeline->x264enc || !pipeline->rtph264pay || !pipeline->udpsink) {
        g_printerr("[E] [ Rush-B -> VideoPipeline ] Elements could not be created.\n");
        return -1;
    }

    //Add elements to the Pipeline
    gst_bin_add_many(GST_BIN(pipeline->pipe),
        pipeline->v4l2src,
        pipeline->videoconvert,
        pipeline->x264enc,
        pipeline->rtph264pay,
        pipeline->udpsink, NULL);

    //Link pipeline elements
    if (gst_element_link_many(pipeline->v4l2src, pipeline->videoconvert, pipeline->x264enc, pipeline->rtph264pay, pipeline->udpsink, NULL) != TRUE) {
        g_printerr("[E] [ Rush-B -> VideoPipeline ] Elements Could Not Be Linked.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    }
    return 0;
}

int32_t VideoPublisher::Destroy_Pipeline()
{
    gst_element_set_state(this->pipeline.pipe, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(this->pipeline.pipe));
    g_print("[I] [ Rush-B -> VideoPipeline ] Publisher Video Pipeline Destroyed\n");
    //memset(pipeline, 0, sizeof(tVideoPipeline));
    return 0;
}

int32_t VideoPublisher::Set_Pipeline_State_Playing()
{
    //Set State to playing
    GstStateChangeReturn ret = gst_element_set_state(pipeline.pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("[E] [ Rush-B -> VideoPipeline ] Unable To Set The Pipeline To The Playing State.\n");
        gst_object_unref(pipeline.pipe);
        return -1;
    } else {
        g_print("[I] [ Rush-B -> VideoPipeline ] Publisher Video Pipeline Set To Playing\n");
    }
    return 0;
}
