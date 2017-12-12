/**
 *      @file  myf.c
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

#include <gtk/gtk.h>
#include <string.h>
#include "myf.h"

/*
CAIRO
  -Context (parametros gráficos)
  -Surface (destino do gráfico, eg fincheiro, janela GTK)
  -Path  (uma ou mais linha)
  -Source (cores, gradientes)
  -Mask (espécie de roi)
*/

/**
 * @brief  void
 *
 * @param  none
 * @return none
 */
 void pari_delete_event(GtkWidget * window, GdkEvent * event, gpointer data) {
   g_print("you should not use the os to force leave");
   gtk_main_quit();
 }


 /**
  * @brief  Callback to catch CTRL-C
  */
 void InterceptCTRL_C(int a)
 {
   g_print("Sair por CTRL-C\n");
   gtk_main_quit();
 }


 /**
  * @brief  Callback to process the "destroy" event
  *
  * Here you can decide whether you keep in the gtk_main loop operation or if you terminate it
  * That is, you can decide to continue with the GUI running or close the GUI, but not necessarily the application
  * Stop the GTK+ main loop function when the window is destroyed.
  * This event only occurs if delete_event returns FALSE
  * @param  window - The widget that generated the event (not used here)
  * @param  data - generic user data (not used here)
  * @return void
  */
 static void pari_destroy(GtkWidget * window, gpointer data)
 {
         puts("Pedido de destruição de janela");
         gtk_main_quit();  //necessary to to leave GTK main loop
 }


 /**
  * @brief  Manage button 3 click with the intention to leave application
  *    Either shows a message or exits
  *
  * @param  w - The Widget ID
  * @param user_data - Custom data with the ID of another widget to check. In this case the switch1
  * @return void
  */
 /*void on_button2_clicked(GtkWidget * widget, gpointer user_data)
 {
   gboolean a=gtk_switch_get_active(GTK_SWITCH(user_data));
   if (a == FALSE)
         printf("Must enable the Quit switch before leaving\n");
   else
   gtk_main_quit();  //necessary to to leave GTK main loop
         //... missing code to terminate the gtk main loop ...
 }*/

 /**
  * @brief  Function to process the text from entry and label
  *
  * @param widget - the one that originated the call
  * @param user_data - Custom data with a widget ID to fetch some info
  * @return void.
  */
 /*void on_button1_clicked(GtkWidget *widget, gpointer user_data)
 {
   GtkEntry *ts = GTK_ENTRY(user_data);
   GtkLabel *lbl= GTK_LABEL(gtk_builder_get_object(builderG,"label3")); //Get some specific label ID to change it
   if(ts) // if ts
   {
         const char* tss = gtk_entry_get_text(ts); //get the text from entry1 widget
         ReverseString(tss);
         printf("Text available in entry1: %s\n", tss);
         gtk_label_set_text(lbl, tss);   //set entry text in "label2" widget
         gtk_widget_hide( GTK_WIDGET(ts) ); // ts is not the valid parameter, so we need to get ts widget
         gtk_widget_show( GTK_WIDGET(ts) ); // ts is not the valid parameter, so we need to get ts widget
   }
 }*/


/**
 * @brief  voids
 *
 * @param  none
 * @return none
 */
 void ReverseString(char *str)
 {
   char c, *t1, *t2, *t3;
   for(t1 = str, t2 = str + strlen(str); t1 < t2;) //notice that 3rd param of for is empty
       c = *t1, *t1++ = *--t2, *t2 = c;

       /*scan all bytes and reverse each multibyte character */
       for(t1 = t2 = str; (c = *t2++);) //notice the parenthesis on "condition" to avoid compiler warning!
       {
         if((c & 0x80) == 0)   // It is a pure ASCII char, no need for more processing!
           t1 = t2;
         else if((c & 0xc0) == 0xc0)   // It is the start of a multibyte, check how many bytes per UTF-8 character
         {
               t3 = t2;
               switch (t2 - t1)
               {
                 case 4:
                   c = *t1, *t1++ = *--t2, *t2 = c;    // fallthrough
                 case 3:                               // fallthrough
                 case 2:
                     c = *t1, *t1++ = *--t2, *t2 = c;
               }
               t2 = t1 = t3;
         }
       }

 }

//Headerrrrrrrrrrrrrrrrrrrrrrrrrrrrr
CvCapture *pari_StartImageAcquisition()
{
        CvCapture *capture = cvCaptureFromCAM(0);              //Capture using 1st camera: i.e., no. 0
        IplImage *frame=cvQueryFrame(capture);                 //Update frame. Pointer does not change.
        src_imageG = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);//create image for color (8 bits, 3 channels)
        dst_imageG = cvClone(src_imageG);                       //create clone of source image
        return capture;
}
//Headerrrrrrrrrrrrrrrrrrrrrr
void pari_PerformImageAcquisition(CvCapture *capt)
{
        static IplImage *frame;
        frame=cvQueryFrame(capt);               //Update frame pointer.
        cvCopy(frame, src_imageG, NULL);        //copy frame as it is (preserve color)
        cvCopy(src_imageG, dst_imageG, NULL);   //copy src into dst and ready to process (admitt similar image structure)
}

// Exemplo de código de uma função que converte
// uma IplImage num pixbuf para inserir numa interface GTK
// e ajusta-a com certas dimensões passadas como argumentos

GdkPixbuf *pari_ConvertOpenCv2Gtk(IplImage * image, int dst_w, int dst_h)
{
    IplImage *gtkMask=image;
    GdkPixbuf *pix, *rpix;
    cvCvtColor(image, gtkMask, CV_BGR2RGB);
    pix = gdk_pixbuf_new_from_data((guchar *) gtkMask->imageData,
                       GDK_COLORSPACE_RGB,
                       FALSE,
                       gtkMask->depth,
                       gtkMask->width,
                       gtkMask->height,
                       gtkMask->widthStep, NULL, NULL);
    rpix = gdk_pixbuf_scale_simple(pix, dst_w, dst_h, GDK_INTERP_BILINEAR); //rescale image
    g_object_unref(pix);  //free the intermediate pixbuf...
    return rpix;
}

//copy from IplImage to pixbuf and paint DA
void pari_RefreshDrawingArea( char * widgetName, IplImage *img)
{
  GtkWidget *da=GTK_WIDGET(gtk_builder_get_object (builderG, widgetName));
  if( ! da )
  {
    printf("failed\n");
    return;
  }
  GdkPixbuf *pix=pari_ConvertOpenCv2Gtk(img, da->allocation.width, da->allocation.height );
  cairo_t *cr = gdk_cairo_create (gtk_widget_get_window(da));
  gdk_cairo_set_source_pixbuf(cr, pix, 0, 0);
  cairo_paint(cr);
  cairo_fill(cr);
  cairo_destroy(cr);
  g_object_unref(pix);  //free the pixbuf...
}

/**
 * @brief  Function to perform some specific operation.
 *
 * @param  src Source image to process
 * @param  dst Image to put the processed result
 * @param  gb  GtkBuilder pointer for the currently loaded GUI.
 * @param  udata1 gpointer for generic data for the operation. Normally the widget name. Return if NULL.
 * @param  udata2 gpointer for generic data for the operation. Normally the widget name for auxiliary parameter. May be ignored.
 */
void pari_ProcessUserOperations(IplImage *src, IplImage *dst)
{
  /*If nothing is to be done at least the dst is the same as src*/
  cvCopy( src, dst, NULL);

  //Now operate all functions accumulated (one after one)
  pari_UserOperation1(dst, dst, builderG, (gpointer)"checkbutton1", ...);
  pari_UserOperation2(dst, dst, builderG, (gpointer)"checkbutton2", ...);
  pari_UserOperation3(dst, dst, builderG, (gpointer)"checkbutton3", ...);
  pari_UserOperation4(dst, dst, builderG, (gpointer)"checkbutton4", ...);
  pari_UserOperation5(dst, dst, builderG, (gpointer)"checkbutton5", ...);
  pari_UserOperation6(dst, dst, builderG, (gpointer)"checkbutton6", ...);
}