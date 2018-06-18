#include <string.h>
#include <stdio.h>
#include <gst/gst.h>
#include <unistd.h>

typedef struct _CustomData {
	GstElement *pipeline,*source,*decoder,*videoconv,*audioconv,*audiosink,*videosink,*resample,*vidbalance;

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





static void change_contrast(CustomData *data,gint flag)
{
	//g_print("in fun\n");
	static gdouble contr=1;
	if(flag==1)
	{
		contr+=0.1;
		g_print("contrast increased to %lf\n",contr);
		if(contr>2)
		{
			g_print("you can't increase more than 2\n");			
			contr=2;
		}
	}
	else
	{
		contr-=0.1;
		g_print("contrast decreased to %lf\n",contr);
		if(contr<0)
		{
			g_print("you can't increase less than 0\n");
			contr=0;
		}
	}
	if(contr==1)
		g_print("Default contrast 1\n");
	g_object_set(G_OBJECT(data->vidbalance),"contrast",contr,NULL);

	sleep(1);
	if(((flag==1)&&(contr<2.0))||((flag==0)&&(contr>1.0)))
		change_contrast(data,flag);
	else return;

	//return;	

}
static void change_brightness(CustomData *data,gint flag)
{
	static gdouble bright=0;
	if(flag==1)
	{
		bright+=0.1;
		g_print("brightness increased to %lf\n",bright);
		if(bright>1)
		{
			g_print("you can't increase more than 1\n");
			bright=1;
		}
	}
	else
	{
		bright-=0.1;
		g_print("brightness decreased to %lf\n",bright);
		if(bright<-1)
		{
			g_print("you can't decrease less than -1\n");
			bright=-1;
		}
	}
	if(bright==0.0)
		g_print("Default brightness 0\n");
	g_object_set(G_OBJECT(data->vidbalance),"brightness",bright,NULL);
	sleep(1);
	if(((flag==1)&&(bright<1.0))||((flag==0)&&(bright>0.0)))
		change_brightness(data,flag);
	else return;
	
}

static void change_saturation(CustomData *data,gint flag)
{
	static gdouble satur=1;
	if(flag==1)
	{
		satur+=0.1;
		g_print("saturation(color) increased to %lf\n",satur);
		if(satur>2)
		{
			g_print("you can't increase more than 2\n");
			satur=2;
		}
	}
	else
	{
		satur-=0.1;
		g_print("saturation(color) decreased to %lf\n",satur);
		if(satur<0)
		{
			g_print("you can't decrease less than 0\n");
			satur=0;
		}
	}
	if(satur==1.0)
		g_print("Default color 0\n");
	g_object_set(G_OBJECT(data->vidbalance),"saturation",satur,NULL);


	sleep(1);
	if(((flag==1)&&(satur<2.0))||((flag==0)&&(satur>1.0)))
		change_saturation(data,flag);
	else return;
	


}

static void display_status(CustomData *data)
{
	gdouble contr,bright,hue_var,satur;
	g_object_get(data->vidbalance,"contrast",&contr,NULL);
	g_object_get(data->vidbalance,"brightness",&bright,NULL);
	g_object_get(data->vidbalance,"hue",&hue_var,NULL);
	g_object_get(data->vidbalance,"saturation",&satur,NULL);
	g_print("contrast[default is 1]:%lf\n",contr);	
	g_print("brightness[default is 0]:%lf\n",bright);
	g_print("hue[default is 0]:%lf\n",hue_var);
	g_print("saturation(color)[default is 1]:%lf\n",satur);

}

static void change_hue(CustomData *data,gint flag)
{
	static gdouble hue_var=0;
	if(flag==1)
	{
		hue_var+=0.1;
		g_print("hue increased to %lf\n",hue_var);
		if(hue_var>1)
		{
			g_print("you can't increase more than 1\n");
			hue_var=1;
		}
	}
	else
	{
		hue_var-=0.1;
		g_print("hue decreased to %lf\n",hue_var);
		if(hue_var<-1)
		{
			g_print("you can't decrease less than -1\n");
			hue_var=-1;
		}
	}
	if(hue_var==0.0)
		g_print("Default hue 0\n");
	g_object_set(G_OBJECT(data->vidbalance),"hue",hue_var,NULL);
	
	sleep(1);
	if(((flag==1)&&(hue_var<1.0))||((flag==0)&&(hue_var>0.0)))
		change_hue(data,flag);
	else return;


}



/* Process keyboard input */
static gboolean handle_keyboard (GIOChannel *source, GIOCondition cond, CustomData *data) {
  gchar *str = NULL;

  if (g_io_channel_read_line (source, &str, NULL, NULL, NULL) != G_IO_STATUS_NORMAL) {
    return TRUE;
  }
  
  switch (g_ascii_tolower (str[0])) {
	case 'b':
		if (g_ascii_isupper (str[0])) 
			change_brightness(data,1);
		else
			change_brightness(data,0);
	
		break;

	case 'c':
		if (g_ascii_isupper (str[0])) 
			change_contrast(data,1);
		else
			change_contrast(data,0);
		
		break;
	case 'h':
		if (g_ascii_isupper (str[0])) 
			change_hue(data,1);
		else
			change_hue(data,0);
		
		break;
	case 'p':
  
		data->playing = !data->playing;
		gst_element_set_state (data->pipeline, data->playing ? GST_STATE_PLAYING : GST_STATE_PAUSED);
		g_print ("Setting state to %s\n", data->playing ? "PLAYING" : "PAUSE");
		break;
	case 's':
		if (g_ascii_isupper (str[0])) 
			change_saturation(data,1);
		else
			change_saturation(data,0);
		
		break;
	case 'd':
		display_status(data);break;

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
    " 'C' to increase contrast, 'c' to decrease contrast\n"
    " 'B' to increase brightness, 'b' to decrease brightness\n"
    " 'H' to increase hue, 'h' to decrease hue\n"
    " 'S' to increase saturation(i.e color), 's' to decrease saturation(i.e color)\n"
    " 'H' to increase hue, 'h' to decrease hue\n"
    " 'd' to know the status of display\n"
    " 'Q' to quit\n");

	//io_stdin = g_io_channel_unix_new (fileno (stdin));
	//io_stdin = g_io_channel_unix_new (fileno (getchar()));
	
	
	//g_io_add_watch (io_stdin, G_IO_IN, (GIOFunc)handle_keyboard, &data); ///watches the keyboard interrupt


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
	data.vidbalance=gst_element_factory_make("videobalance","videobal");
	if(!data.vidbalance){
                g_print("Failed to create videobalance\n");
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



	if (!data.pipeline || !data.source || !data.decoder || !data.videoconv || !data.vidbalance || !data.videosink || !data.audioconv || !data.resample || !data.audiosink) {
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
			data.source,data.decoder,data.audiosink,data.vidbalance,data.videosink,data.resample,data.audioconv,data.videoconv,NULL);
	/* we link the elements together */
	gst_element_link (data.source, data.decoder);
	//gst_element_link (data.decoder,data.videoconv);
	gst_element_link (data.decoder,data.vidbalance);
	gst_element_link (data.vidbalance,data.videoconv);
	gst_element_link (data.videoconv,data.videosink);

	gst_element_link (data.decoder,data.audioconv);
        gst_element_link (data.audioconv, data.resample);

	gst_element_link (data.resample,data.audiosink);



	//g_signal_connect (data.decoder, "pad-added", G_CALLBACK (on_pad_added), data.videoconv);
	g_signal_connect (data.decoder, "pad-added", G_CALLBACK (on_pad_added), data.vidbalance);
	g_signal_connect (data.vidbalance, "pad-added", G_CALLBACK (on_pad_added), data.videoconv);
	g_signal_connect(data.videoconv, "pad-added", G_CALLBACK(on_pad_added), data.videosink);   
	//g_signal_connect (decoder, "pad-added", G_CALLBACK (on_pad_added), videosink);

	g_signal_connect(data.decoder,"pad-added",G_CALLBACK(on_pad_added),data.audioconv);
	g_signal_connect(data.audioconv,"pad-added",G_CALLBACK(on_pad_added),data.resample);
        g_signal_connect(data.resample,"pad-added",G_CALLBACK(on_pad_added),data.audiosink);
	gint i=0;
	

	/* Set the pipeline to "playing" state*/
	g_print ("Now playing: %s\n", argv[1]);
	ret=gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
	
	change_brightness(&data,1);
	change_brightness(&data,0);
		

	change_contrast(&data,1);
	change_contrast(&data,0);

	change_hue(&data,1);
	change_hue(&data,0);

	change_saturation(&data,1);
	change_saturation(&data,0);


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






