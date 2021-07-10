#include "VideoPipeline.h"

VideoSubscriber::VideoSubscriber() { }
VideoSubscriber::~VideoSubscriber() { }

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
    g_print("[I] [ Control-Center -> VideoPipeline ] A new pad %s was created\n", name);

    caps = gst_pad_get_pad_template_caps(pad);
    description = gst_caps_to_string(caps);
    g_free(description);

    video_convert = GST_ELEMENT(data);

    if (!gst_element_link_pads(element, name, video_convert, "sink")) {
        g_printerr("[E] [ Control-Center -> VideoPipeline ] Failed to link elements 3\n");
    }

    g_free(name);
}

int32_t VideoSubscriber::Construct_Pipeline(const char* name, tVideoPipeline* const pipeline)
{
    //Create Elements
    pipeline->udpsrc = gst_element_factory_make("udpsrc", NULL);
    g_object_set(pipeline->udpsrc, "port", port, NULL);

    //Init the caps for the filter
    GstCaps* caps = gst_caps_new_simple("application/x-rtp",
        "media", G_TYPE_STRING, "video",
        "clock-rate", G_TYPE_INT, 90000,
        "encoding-name", G_TYPE_STRING, "H264",
        "payload", G_TYPE_INT, 96, NULL);

    pipeline->filter = gst_element_factory_make("capsfilter", "filter");
    g_object_set(G_OBJECT(pipeline->filter), "caps", caps, NULL);
    gst_caps_unref(caps);

    pipeline->rtph264depay = gst_element_factory_make("rtph264depay", NULL);
    pipeline->decodebin = gst_element_factory_make("decodebin", NULL);
    pipeline->videoconvert = gst_element_factory_make("videoconvert", NULL);
    pipeline->queue = gst_element_factory_make("queue", NULL);
    pipeline->autovideosink = gst_element_factory_make("autovideosink", NULL);

    //Create Empty Pipeline
    pipeline->pipe = gst_pipeline_new(name);

    if (!pipeline->pipe || !pipeline->udpsrc || !pipeline->filter || !pipeline->rtph264depay || !pipeline->decodebin || !pipeline->videoconvert || !pipeline->queue || !pipeline->autovideosink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    //Add elements to the Pipeline
    gst_bin_add_many(GST_BIN(pipeline->pipe),
        pipeline->udpsrc,
        pipeline->filter,
        pipeline->rtph264depay,
        pipeline->decodebin,
        pipeline->videoconvert, NULL);

    //Link udpsrc through to decode bin
    if (gst_element_link_many(
            pipeline->udpsrc,
            pipeline->filter,
            pipeline->rtph264depay,
            pipeline->decodebin, NULL)
        != TRUE) {
        g_printerr("[E] [ Control-Center -> VideoPipeline ] Elements could not be linked.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    }

    //Callback used to link decode bin and autovideo sink
    g_signal_connect(pipeline->decodebin, "pad-added", G_CALLBACK(Pad_Callback), pipeline->videoconvert);

    //Add and link the sink to the videoconverter
    gst_bin_add_many(GST_BIN(pipeline->pipe),
        pipeline->queue,
        pipeline->autovideosink, NULL);

    if (gst_element_link_many(
            pipeline->videoconvert,
            pipeline->queue,
            pipeline->autovideosink, NULL)
        != TRUE) {
        g_printerr("[E] [ Control-Center -> VideoPipeline ] Elements could not be linked.\n");
        gst_object_unref(pipeline->pipe);
        return -1;
    }

    return 0;
}

int32_t VideoSubscriber::Destroy_Pipeline()
{
    gst_element_set_state(this->pipeline.pipe, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(this->pipeline.pipe));
    g_print("[I] [ Control-Center -> VideoPipeline ] Subscriber Video Pipeline destroyed\n");
    //memset(pipeline, 0, sizeof(tVideoPipeline));
    return 0;
}

int32_t VideoSubscriber::Set_Pipeline_State_Playing()
{
    //Set State to playing
    GstStateChangeReturn ret = gst_element_set_state(pipeline.pipe, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("[E] [ Control-Center -> VideoPipeline ] Unable to set the pipeline to the playing state.\n");
        gst_object_unref(pipeline.pipe);
        return -1;
    } else {
         g_print("[I] [ Control-Center -> VideoPipeline ] Subscriber Video Pipeline set to playing\n");
    }
    return 0;
}

void VideoSubscriber::Start_Gloop()
{
    //Start the the main loop
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
}
