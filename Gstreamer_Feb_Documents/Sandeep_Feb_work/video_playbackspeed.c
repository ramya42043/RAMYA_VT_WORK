#include <string.h>
#include <stdio.h>
#include <gst/gst.h>

typedef struct _CustomData {
	GstElement *pipeline,*source,*decoder,*videoconv,*audioconv,*audiosink,*videosink,*resample;

	GMainLoop *loop;
	GstBus *bus;
	guint bus_watch_id;
	gboolean playing;  /* Playing or Paused */
	gdouble rate;      /* Current playback rate (can be negative) */
} CustomData;


static gboolean
bus_call (GstBus *bus,GstMessage *msg,gpointer data)

{
	GMainLoop *loop = (GMainLoop *) data;
	switch (GST_MESSAGE_TYPE (msg)) {
		case GST_MESSAGE_EOS:
			g_print ("End of stream\n");
			g_main_loop_quit (loop);
			break;
		case GST_MESSAGE_ERROR: {
						gchar *debug;
						GError *error;
						gst_message_parse_error (msg, &error, &debug);
						g_free (debug);
						g_printerr ("Error: %s\n", error->message);
						g_error_free (error);
						g_main_loop_quit (loop);
						break;
					}
		default:
					break;
	}
	return TRUE;
}

static void on_pad_added (GstElement *element,GstPad *pad,gpointer data)
{
	GstPad *sinkpad;

	GstElement *decoder = (GstElement *) data;


	/* We can now link this pad with the vorbis-decoder sink pad */
	g_print ("Dynamic pad created, linking demuxer/decoder\n");
	sinkpad = gst_element_get_static_pad (decoder, "sink");
	gst_pad_link (pad, sinkpad);
	gst_object_unref (sinkpad);
}




static void send_seek_event (CustomData *data) {
  gint64 position;
  GstEvent *seek_event;

  /* Obtain the current position, needed for the seek event */
  if (!gst_element_query_position (data->pipeline, GST_FORMAT_TIME, &position)) {
    g_printerr ("Unable to retrieve current position.\n");
    return;
  }
	

  /* Create the seek event */
  if (data->rate > 0) {
    seek_event = gst_event_new_seek (data->rate, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,
        GST_SEEK_TYPE_SET, position, GST_SEEK_TYPE_SET, -1);
  } else {
    seek_event = gst_event_new_seek (data->rate, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH | GST_SEEK_FLAG_ACCURATE,
        GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_SET, position);
  }

  if (data->videosink == NULL) {
    /* If we have not done so, obtain the sink through which we will send the seek events */
	
    
	g_object_get (data->pipeline, "videosink", &data->videosink, NULL);
  }

  /* Send the event */
  gst_element_send_event (data->videosink, seek_event);

  g_print ("Current rate: %g\n", data->rate);
}


/* Process keyboard input */
static gboolean handle_keyboard (GIOChannel *source, GIOCondition cond, CustomData *data) {
  gchar *str = NULL;

  if (g_io_channel_read_line (source, &str, NULL, NULL, NULL) != G_IO_STATUS_NORMAL) {
    return TRUE;
  }
  g_print("%s\n",str);
  switch (g_ascii_tolower (str[0])) {
  case 'p':
  //case ' ':
    data->playing = !data->playing;
    gst_element_set_state (data->pipeline, data->playing ? GST_STATE_PLAYING : GST_STATE_PAUSED);
    g_print ("Setting state to %s\n", data->playing ? "PLAYING" : "PAUSE");
    break;
  case 's':
    if (g_ascii_isupper (str[0])) {
      data->rate *= 2.0;
    } else {
      data->rate /= 2.0;
    }
    send_seek_event (data);
    break;
  case 'd':
    data->rate *= -1.0;
    send_seek_event (data);
    break;
  case 'n':
    if (data->videosink == NULL) {
      /* If we have not done so, obtain the sink through which we will send the step events */
	
      g_object_get (data->pipeline, "videosink", &data->videosink, NULL);
    }

    gst_element_send_event (data->videosink,
        gst_event_new_step (GST_FORMAT_BUFFERS, 1, data->rate, TRUE, FALSE));
    g_print ("Stepping one frame\n");
    break;
  case 'q':
    g_main_loop_quit (data->loop);
    break;
  default:
    break;
  }

  g_free (str);

  return TRUE;
}


int main (int argc,char *argv[])
{
	CustomData data;
	GstStateChangeReturn ret;
	GIOChannel *io_stdin;
	gst_init (&argc, &argv);
	memset (&data, 0, sizeof (data));
	data.loop = g_main_loop_new (NULL, FALSE);


	/* Print usage map */
	g_print (
    "USAGE: Choose one of the following options, then press enter:\n"
    " 'P' to toggle between PAUSE and PLAY\n"
    " 'S' to increase playback speed, 's' to decrease playback speed\n"
    " 'D' to toggle playback direction\n"
    " 'N' to move to next frame (in the current direction, better in PAUSE)\n"
    " 'Q' to quit\n");

	io_stdin = g_io_channel_unix_new (fileno (stdin));
	//io_stdin = g_io_channel_unix_new (fileno (getchar()));
	
	
	g_io_add_watch (io_stdin, G_IO_IN, (GIOFunc)handle_keyboard, &data); ///watches the keyboard interrupt


	/* Check input arguments */
	if (argc != 2) {
		g_printerr ("Usage: %s <mp4> filename>\n", argv[0]);
		return -1;
	}
	/* Create gstreamer elements */
	data.pipeline = gst_pipeline_new ("videoplayer");
	data.source = gst_element_factory_make ("filesrc", "src");

	if(!data.source){
		g_print("Failed to create source\n");
		return -1;
	}

	data.decoder = gst_element_factory_make ("decodebin", "video decoder");
	//decoder = gst_element_factory_make ("dvdec", "video decoder");
	if(!data.decoder){
		g_print("Failed to create  video decoder\n");
		return -1;
	}

	data.videoconv = gst_element_factory_make ("videoconvert", "video conversion");
        if(!data.videoconv){
                g_print("Failed to create videoconverter\n");
                return -1;
        }



	data.videosink = gst_element_factory_make ("xvimagesink", "video output");
	if(!data.videosink){
		g_print("Failed to create videosink\n");
		return -1;
	}

	data.audioconv = gst_element_factory_make ("audioconvert", "audio conversion");
	if(!data.audioconv){
		g_print("Failed to create audio conv\n");
		return -1;
	}

	data.resample = gst_element_factory_make ("audioresample", "audio sample");
        if(!data.resample){
                g_print("Failed to create audio sample\n");
                return -1;
        }

	
	data.audiosink = gst_element_factory_make ("alsasink", "audio-output");
        if(!data.audiosink){
                g_print("Failed to create audio sink\n");
                return -1;
        }



	if (!data.pipeline || !data.source || !data.decoder || !data.videoconv || !data.videosink || !data.audioconv || !data.resample || !data.audiosink) {
		g_printerr ("One element could not be created. Exiting.\n");
		return -1;
	}
	/* Set up the pipeline */
	/* we set the input filename to the source element */
	g_object_set (G_OBJECT (data.source), "location", argv[1], NULL);
	/* we add a message handler */
	data.bus = gst_pipeline_get_bus (GST_PIPELINE (data.pipeline));
	g_print("bus created\n");
	data.bus_watch_id=gst_bus_add_watch (data.bus, bus_call, data.loop);
	gst_object_unref (data.bus);
	/* we add all elements into the pipeline */
	gst_bin_add_many (GST_BIN (data.pipeline),
			data.source,data.decoder,data.audiosink,data.videosink,data.resample,data.audioconv,data.videoconv,NULL);
	/* we link the elements together */
	gst_element_link (data.source, data.decoder);
	gst_element_link (data.decoder,data.videoconv);
	gst_element_link (data.videoconv,data.videosink);

	gst_element_link (data.decoder,data.audioconv);
        gst_element_link (data.audioconv, data.resample);

	gst_element_link (data.resample,data.audiosink);



	g_signal_connect (data.decoder, "pad-added", G_CALLBACK (on_pad_added), data.videoconv);
	g_signal_connect(data.videoconv, "pad-added", G_CALLBACK(on_pad_added), data.videosink);   
	//g_signal_connect (decoder, "pad-added", G_CALLBACK (on_pad_added), videosink);

	g_signal_connect(data.decoder,"pad-added",G_CALLBACK(on_pad_added),data.audioconv);
	g_signal_connect(data.audioconv,"pad-added",G_CALLBACK(on_pad_added),data.resample);
        g_signal_connect(data.resample,"pad-added",G_CALLBACK(on_pad_added),data.audiosink);



	/* Set the pipeline to "playing" state*/
	g_print ("Now playing: %s\n", argv[1]);
	ret=gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
	
	if (ret == GST_STATE_CHANGE_FAILURE) {
		g_printerr ("Unable to set the pipeline to the playing state.\n");
		gst_object_unref (data.pipeline);
		return -1;
	}
	data.playing = TRUE;
	data.rate = 1.0;

	/* Create a GLib Main Loop and set it to run */
	data.loop = g_main_loop_new (NULL, FALSE);
	g_main_loop_run (data.loop);

	/* Free resources */
	g_main_loop_unref (data.loop);
	g_io_channel_unref (io_stdin);
	gst_element_set_state (data.pipeline, GST_STATE_NULL);
	/*if (data.videosink != NULL)
	{	
		g_print("unref\n");
		gst_object_unref (data.videosink);
	}*/
	gst_object_unref (data.pipeline);
	return 0;


	
} 






