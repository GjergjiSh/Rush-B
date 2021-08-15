#include "VideoPipeline.h"

static GstBusSyncReply Bus_Message_Callback(GstBus* bus, GstMessage* message, gpointer pipeline)
{
    switch (GST_MESSAGE_TYPE(message)) {
    case GST_MESSAGE_ERROR:
        gchar* debug;
        GError* error;
        gst_message_parse_error(message, &error, &debug);
        g_free(debug);
        g_printerr("[E] [ Bus : VideoPipeline ] %s\n", error->message);
        g_error_free(error);
        break;

    default:
        break;
    }
    return GST_BUS_PASS;
}

/********************************************************************************************************************************
 * @note: Used to link decodebin and videoconvert.
 * Decodebin uses something called a "sometimes-pad", which is basically a pad that will show up when a certain condition is met,
 * in decodebin's case that is media being decoded. gst-launch will do this sort of thing automagically,
 * but in code you need to register a callback, and then link the pad in that callback
 ********************************************************************************************************************************/
static void Pad_Callback(GstElement* element, GstPad* pad, gpointer data)
{
    gchar* name;
    GstCaps* caps;
    gchar* description;
    GstElement* video_convert;

    name = gst_pad_get_name(pad);
    g_print("[I] [ Bus : VideoPipeline ] A new pad %s was created\n", name);

    caps = gst_pad_get_pad_template_caps(pad);
    description = gst_caps_to_string(caps);
    g_free(description);

    video_convert = GST_ELEMENT(data);

    if (!gst_element_link_pads(element, name, video_convert, "sink")) {
        g_printerr("[E] [ Bus : VideoPipeline ] Failed to link decidebin and autoconvert \n");
    }

    g_free(name);
}

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
    this->pipeline->pipe = gst_pipeline_new("Subscriber Video Pipeline");
    this->pipeline->udpsrc = gst_element_factory_make("udpsrc", NULL);
    this->pipeline->filter = gst_element_factory_make("capsfilter", NULL);
    this->pipeline->rtph264depay = gst_element_factory_make("rtph264depay", NULL);
    this->pipeline->decodebin = gst_element_factory_make("decodebin", NULL);
    this->pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    this->pipeline->queue = gst_element_factory_make("queue", NULL);
    this->pipeline->autovideosink = gst_element_factory_make("autovideosink", NULL);

    if (!pipeline->pipe ||
        !this->pipeline->udpsrc ||
        !this->pipeline->filter ||
        !this->pipeline->rtph264depay ||
        !this->pipeline->decodebin ||
        !this->pipeline->videoconvert ||
        !this->pipeline->queue ||
        !this->pipeline->autovideosink) {
        g_printerr("[I] [ Bus : VideoPipeline ] Failed to create all pipeline elements\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(this->pipeline->pipe),
        this->pipeline->udpsrc,
        this->pipeline->filter,
        this->pipeline->rtph264depay,
        this->pipeline->decodebin,
        this->pipeline->videoconvert,
        this->pipeline->queue,
        this->pipeline->autovideosink, NULL);

    return 0;
}

int32_t VideoPipeline::Configure_Elements()
{
    GstCaps* caps = gst_caps_new_simple("application/x-rtp",
        "media", G_TYPE_STRING, "video",
        "clock-rate", G_TYPE_INT, 90000,
        "encoding-name", G_TYPE_STRING, "H264",
        "payload", G_TYPE_INT, 96, NULL);

    g_object_set(G_OBJECT(this->pipeline->udpsrc), "port", port, NULL);
    g_object_set(G_OBJECT(this->pipeline->filter), "caps", caps, NULL);
    gst_caps_unref(caps);

    g_signal_connect(this->pipeline->decodebin, "pad-added", G_CALLBACK(Pad_Callback), this->pipeline->videoconvert);
    GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(this->pipeline->pipe));
    gst_bus_add_signal_watch(bus);
    g_signal_connect(bus, "message", (GCallback)Bus_Message_Callback, this->pipeline->pipe);

    return 0;
}

int32_t VideoPipeline::Link_Elements()
{
    if (!gst_element_link_many(
            this->pipeline->udpsrc,
            this->pipeline->filter,
            this->pipeline->rtph264depay,
            this->pipeline->decodebin, NULL)) {
        g_printerr("[E] [ Bus : VideoPipeline ] Failed to link first branch of pipeline elements.\n");
        gst_object_unref(this->pipeline->pipe);
        return -1;
    }

    if (!gst_element_link_many(
            this->pipeline->videoconvert,
            this->pipeline->queue,
            this->pipeline->autovideosink, NULL)) {
        g_printerr("[E] [ Bus : VideoPipeline ] Failed to link second branch of pipeline elements.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    }
    return 0;
}

int32_t VideoPipeline::Destroy_Pipeline()
{
    gst_element_set_state(this->pipeline->pipe, GST_STATE_NULL);
    g_object_unref(this->pipeline->pipe);
    printf("[I] [ Bus : VideoPipeline ] Subscriber Video Pipeline destroyed\n");
    return 0;
}

int32_t VideoPipeline::Set_Pipeline_State_Playing()
{
    GstStateChangeReturn ret = gst_element_set_state(this->pipeline->pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("[E] [ Bus : VideoPipeline ] Unable to set the pipeline to the playing state.\n");
        gst_object_unref(this->pipeline->pipe);
        return -1;
    }
    g_print("[I] [ Bus : VideoPipeline ] Subscriber Video Pipeline set to playing\n");
    return 0;
}

void VideoPipeline::Start_Gloop()
{
    loop = g_main_loop_new(NULL, FALSE);
    this->video_thread = std::thread(g_main_loop_run, loop);
    this->video_thread.detach();
}

