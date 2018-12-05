#ifndef __GTK_MODULE__
#define __GTK_MODULE__

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void screen_changed(GtkWidget *widget, GdkScreen *old_screen, gpointer user_data);
static gboolean draw(GtkWidget *widget, cairo_t *new_cr, gpointer user_data);

class GTK_MODULE{
public:
    void init(int* int_ptr);
};

#endif