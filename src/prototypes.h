/*File generated automatically in joana-X541UV by joana on Qua Dez  6 11:41:36 WET 2017*/
#ifdef __cplusplus
extern "C" {
#endif
/* callbacks.c */
void on_drawingarea1_draw (GtkWidget * widget, cairo_t * cr, gpointer user_data);
void on_drawingarea1_motion_notify_event (GtkWidget * widget, GdkEventMotion * event, gpointer user_data);
void on_drawingarea1_scroll_event (GtkWidget * widget, GdkEventScroll * event, gpointer user_data);
void on_mouse_button_on (GtkWidget * widget, GdkEventButton * event, gpointer user_data);
gboolean p_ForceRefreshDA (gpointer user_data);
void p_InitTimer ();
void p_RedrawFreeForm (cairo_t * cr);
void p_RedrawText (cairo_t * cr);
gboolean pari_UpdateImageAreas (gpointer data);
/* main.c */
int main (int argc, char *argv[]);
/* myf.c */
void InterceptCTRL_C (int a);
void ReverseString (char *str);
void on_button1_clicked (GtkWidget * widget, gpointer user_data);
void on_button2_clicked (GtkWidget * widget, gpointer user_data);
GdkPixbuf *pari_ConvertOpenCv2Gtk (IplImage * image, int dst_w, int dst_h);
void pari_PerformImageAcquisition (CvCapture * capt);
void pari_RefreshDrawingArea (char *widgetName, IplImage * img);
CvCapture *pari_StartImageAcquisition ();
void pari_delete_event (GtkWidget * window, GdkEvent * event, gpointer data);
static void pari_destroy (GtkWidget * window, gpointer data);
#ifdef __cplusplus
}
#endif
