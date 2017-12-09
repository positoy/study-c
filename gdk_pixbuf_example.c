#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char* argv[])
{
    GdkPixbuf* srcbuf;
    GdkPixbuf* dstbuf;
    GError* error = NULL;
    int w,h;

    gtk_init(&argc, &argv);

    if ((srcbuf = gdk_pixbuf_new_from_file("./che.jpg", &error)) == FALSE) {
        fprintf(stderr, "file read error\n");
        exit(1);
    }

    w = gdk_pixbuf_get_width(srcbuf);
    h = gdk_pixbuf_get_height(srcbuf);

    dstbuf = gdk_pixbuf_scale_simple(srcbuf, w/2, h/2, GDK_INTERP_BILINEAR);

    if (gdk_pixbuf_save(dstbuf, "./che_resize.jpg", "jpeg", &error, "quality", "90", NULL) == FALSE) {
        fprintf(stderr, "file write error");
        exit(1);
    }

    g_object_unref(srcbuf);
    g_object_unref(dstbuf);
}
