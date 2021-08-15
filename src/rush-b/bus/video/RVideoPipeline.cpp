#include <RVideoPipeline.h>

int32_t VideoPipeline::Construct_Pipeline()
{
    this->pipeline = std::make_shared<tVideoPipeline>();
    int32_t status = 0;

    gst_init(NULL, NULL);
    status = Create_Elements();
    if (status == 0) status = Configure_Elements();
    if (status == 0) status = Link_Elements();
    if (status == 0) g_print("[I] [ Bus : VideoPipeline ] Video Pipeline successfuly constructed\n");
    return status;
}

int32_t VideoPipeline::Create_Elements()
{
    this->pipeline->pipe = gst_pipeline_new("Publisher VideoPipeline");
    this->pipeline->v4l2src = gst_element_factory_make("v4l2src", NULL);
    this->pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    this->pipeline->x264enc = gst_element_factory_make("x264enc", NULL);
    this->pipeline->rtph264pay = gst_element_factory_make("rtph264pay", NULL);
    this->pipeline->udpsink = gst_element_factory_make("udpsink", NULL);

    if (!pipeline->pipe ||
        !this->pipeline->v4l2src ||
        !this->pipeline->videoconvert ||
        !this->pipeline->x264enc ||
        !this->pipeline->rtph264pay ||
        !this->pipeline->udpsink) {
        g_printerr("[E] [ Bus : VideoPipeline ] Elements could not be created.\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(pipeline->pipe),
        this->pipeline->v4l2src,
        this->pipeline->videoconvert,
        this->pipeline->x264enc,
        this->pipeline->rtph264pay,
        this->pipeline->udpsink, NULL);

    return 0;
}

int32_t VideoPipeline::Configure_Elements()
{
    g_object_set(pipeline->v4l2src, "device", this->camera.c_str(), NULL);
    g_object_set(pipeline->x264enc, "tune", 4, NULL);
    g_object_set(pipeline->x264enc, "speed-preset", 1, NULL);
    g_object_set(pipeline->x264enc, "bitrate", 2000, NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "host", this->camera_subscriber_host.c_str(), NULL);
    g_object_set(G_OBJECT(pipeline->udpsink), "port", this->camera_subscriber_port, NULL);

    return 0;
}

int32_t VideoPipeline::Link_Elements()
{
    if (!gst_element_link_many(pipeline->v4l2src, pipeline->videoconvert, pipeline->x264enc, pipeline->rtph264pay, pipeline->udpsink, NULL)) {
        g_printerr("[E] [ Bus : VideoPipeline ] Elements Could Not Be Linked.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    }
    return 0;
}

int32_t VideoPipeline::Destroy_Pipeline()
{
    gst_element_set_state(this->pipeline->pipe, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(this->pipeline->pipe));
    g_print("[I] [ Bus : VideoPipeline ] Publisher Video Pipeline Destroyed\n");
    return 0;
}

int32_t VideoPipeline::Set_Pipeline_State_Playing()
{
    GstStateChangeReturn ret = gst_element_set_state(pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("[E] [ Bus : VideoPipeline ] Unable To Set The Pipeline To The Playing State.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    } else {
        g_print("[I] [ Bus : VideoPipeline ] Publisher Video Pipeline Set To Playing\n");
    }
    return 0;
}
