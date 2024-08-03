#include <gtk/gtk.h>
#include "parser.h"
#include "color.h"

#define PIXEL_SIZE 1

surface_properties properties;
color* color_vec = NULL;

static void draw_callback(GtkWidget *widget, cairo_t *cr) {
    for (int i = 0; i < (int)properties.width; i++) {
        for (int j = 0; j < (int)properties.height; j++) {
            color c_index = color_vec[i * properties.width + j];
            GdkRGBA color = {c_index.r/ 255.0, c_index.g/ 255.0, c_index.b/ 255.0, 1.0};
            gdk_cairo_set_source_rgba(cr, &color);
            cairo_rectangle(cr, j , i , PIXEL_SIZE, PIXEL_SIZE);
            cairo_fill(cr);
        }
    }
}

int main(int argc, char *argv[]) 
{
    FILE* file = open_file("image.ppm");
    properties = read_config(file);
    print_config(properties);
    color_vec = read_pixels(file, properties);
    close_file(file);
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PPMVIEWER");
    gtk_window_set_default_size(GTK_WINDOW(window), properties.width * PIXEL_SIZE, properties.height * PIXEL_SIZE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, properties.width * PIXEL_SIZE, properties.height * PIXEL_SIZE);
    g_signal_connect(drawing_area, "draw", G_CALLBACK(draw_callback), NULL);

    gtk_container_add(GTK_CONTAINER(window), drawing_area);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}