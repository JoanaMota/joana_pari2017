/**
 *      @file  main.c
 *      @brief  Programa Principal
 *
 * Descrição mais detalhada do ficheiro
 *
 *     @author  Miguel Gaspar, miguel.gaspar124@ua.pt
 *
 *   @internal
 *     Created  27-Sep-2017
 *     Company  University of Aveiro
 *   Copyright  Copyright (c) 2017, Miguel Gaspar
 *
 ***************************************************
 */

#define _MAIN_C_
#include <cairo.h>
#include <gtk/gtk.h>
#include "myf.h"


int main(int argc, char *argv[])
{
        gtk_init(&argc, &argv);
        /* load the interface after a configuration file*/
        builderG = gtk_builder_new();
        gtk_builder_add_from_file(builderG, "mydr2.glade", NULL);
        /* connect the signals in the interface */
        gtk_builder_connect_signals(builderG, NULL);

        /* get main window Widget ID and connect special signals */
        GtkWidget *t = GTK_WIDGET(gtk_builder_get_object(builderG, "window1"));
        if(t)
        {
                g_signal_connect(G_OBJECT(t), "delete_event", G_CALLBACK(pari_delete_event), NULL);
        }
        

        // use signal to catch SIGINT  (CTRL-C) - optional
        signal(SIGINT, InterceptCTRL_C);

        p_InitTimer();
       
        g_timeout_add(30, (GSourceFunc) pari_UpdateImageAreas, (gpointer) NULL);
        captureG=pari_StartImageAcquisition();
       
        /* start the event loop */
        gtk_main();

        cvReleaseCapture(&captureG);             //Release capture device.
        cvReleaseImage(&dst_imageG);             //Release image (free pointer when no longer used)
        cvReleaseImage(&src_imageG);             //Release image (free pointer when no longer used).
        return 0;


}
