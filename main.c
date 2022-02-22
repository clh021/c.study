#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdio.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // for strtol
#include <assert.h>

int printVersion() {
    printf("GTK+ version: %d.%d.%d\n", gtk_major_version,
           gtk_minor_version, gtk_micro_version);
    printf("Glib version: %d.%d.%d\n", glib_major_version,
           glib_minor_version, glib_micro_version);
    return 0;
}
int getX11ID(int argc, char *argv[]) {
    char *p;
    int x11ID;
    if (argc == 2) {
    } else {
        fprintf(stderr, "有且需要一个参数: X11ID");
        return -1;
    }
    errno = 0;
    long conv = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
//        printf("error");
    } else {
        x11ID = conv;
    }
    return x11ID;
}
GdkWindow* getGdkWin(Window xid) {
    return gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), xid);
}
void checkWin(GdkWindow* gdkWin) {
    int x,y,width,height;
    gdk_window_get_geometry(gdkWin, &x, &y, &width, &height);
    printf("获取到的坐标是: %d,%d ; 宽高: %d, %d\n", x, y, width, height);
}
void more() {
//    Window win = gdk_x11_window_get_xid(win_cr);
//    printf("win: %d \n", win);
//    const gchar* title;
//    title = 's';
//    gdk_window_set_title(win_cr, title);
//    GtkWindow *win;
//    GdkWindow *window = gtk_widget_get_window(win);
//    const Window xwin = GDK_WINDOW_XID(win_cr);
//    Display * const display=GDK_WINDOW_XDISPLAY(win_cr);
}
gboolean self_gtk_configure_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
//    e = static_cast(event, &GdkEventConfigure); // CONTINUE
}
gboolean self_gtk_key_press_event(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    GdkWindow *window = gtk_widget_get_window(widget);

    GdkWindowState state = gdk_window_get_state(GDK_WINDOW(window));

    switch(event->keyval) {
        case GDK_KEY_F11:
            if (state & GDK_WINDOW_STATE_FULLSCREEN) {
                gtk_window_unfullscreen(GTK_WINDOW(widget));
            }
            else {
                gtk_window_fullscreen(GTK_WINDOW(widget));
            }
            break;
        case GDK_KEY_Escape:
            gtk_main_quit ();
            break;
    }
}
int debugSelfWin() {
    GtkWidget *win;
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size (GTK_WINDOW(win), 640, 400);
    g_signal_connect(G_OBJECT(win), "key-press-event", G_CALLBACK(self_gtk_key_press_event), win);
    g_signal_connect(G_OBJECT(win), "configure-event", G_CALLBACK(self_gtk_configure_event), win);
    gtk_widget_show_all(win);
}
int main(int argc, char *argv[]) {
//    int x11ID = getX11ID(argc, argv);
//    assert(x11ID > 0);
//    printf("X11ID: %d \n", x11ID);

    gtk_init(&argc, &argv);

    // 获取窗口
    gint64 xid = 0x7200005;//g_ascii_strtoll(x11ID, NULL, 16);
    printf("xid: %d \n", xid);
    GdkWindow *gdkWin = getGdkWin((xid));
    checkWin(gdkWin);

    GdkWindowState state = gdk_window_get_state(gdkWin);
    printf("state: %d\n", state);
    printf("size of state: %ld\n", sizeof(state));

//    gdk_window_get_state(gdkWin);
//    gtk_widget_get_state(gtkWin);
//    gtk_widget_get_state_flags(gtkWin);
//    gtk_widget_get_parent_window(gtkWin);

    debugSelfWin();
    gtk_main();
    return 0;
}
