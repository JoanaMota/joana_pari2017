/**
 *      @file  myf.h
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

#define YES 1
#define NO 0

#ifndef _MYF_H
#define _MYF_H
#include <gtk/gtk.h>
#include <cairo.h>
#define MAXFFBUFFER 1000
#include <cv.h>
#include <highgui.h>

typedef struct {
        int count;
        double x[MAXFFBUFFER];
        double y[MAXFFBUFFER];
} free_form;

#ifdef _MAIN_C_
        GtkBuilder *builderG;
        double xoffG=50;
        double yoffG=90;
        double fontSizeFactorG=15;
        free_form ffG={0};   //init count to zero. Do not affect x and y.
        IplImage *dst_imageG , *src_imageG;
        CvCapture *captureG;

#else
        extern GtkBuilder *builderG;
        extern double xoffG;
        extern double yoffG;
        extern free_form ffG;
        extern double fontSizeFactorG;
        extern IplImage *dst_imageG , *src_imageG;
        extern CvCapture *captureG;
#endif


#include "prototypes.h"
#endif  /*_MYF_H */
