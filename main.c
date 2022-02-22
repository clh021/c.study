#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdio.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // for strtol
#include <assert.h>  // for assert
#include <X11/Xlib.h>

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


/* window states */

typedef enum {
    WINDOW_STATE_NONE               = 0,
    WINDOW_STATE_MODAL              = (1 << 0),
    WINDOW_STATE_STICKY             = (1 << 1),
    WINDOW_STATE_MAXIMIZED_VERT     = (1 << 2),
    WINDOW_STATE_MAXIMIZED_HORZ     = (1 << 3),
    WINDOW_STATE_MAXIMIZED          = (WINDOW_STATE_MAXIMIZED_VERT | WINDOW_STATE_MAXIMIZED_HORZ),
    WINDOW_STATE_SHADED             = (1 << 4),
    WINDOW_STATE_SKIP_TASKBAR       = (1 << 5),
    WINDOW_STATE_SKIP_PAGER         = (1 << 6),
    WINDOW_STATE_HIDDEN             = (1 << 7),
    WINDOW_STATE_FULLSCREEN         = (1 << 8),
    WINDOW_STATE_ABOVE              = (1 << 9),
    WINDOW_STATE_BELOW              = (1 << 10),
    WINDOW_STATE_DEMANDS_ATTENTION  = (1 << 11),
    WINDOW_STATE_FOCUSED            = (1 << 12),
    WINDOW_STATE_SIZE               = 13,
} window_state_t;

/* state names */

static char* WINDOW_STATE_NAMES[] = {
        "_NET_WM_STATE_MODAL",
        "_NET_WM_STATE_STICKY",
        "_NET_WM_STATE_MAXIMIZED_VERT",
        "_NET_WM_STATE_MAXIMIZED_HORZ",
        "_NET_WM_STATE_SHADED",
        "_NET_WM_STATE_SKIP_TASKBAR",
        "_NET_WM_STATE_SKIP_PAGER",
        "_NET_WM_STATE_HIDDEN",
        "_NET_WM_STATE_FULLSCREEN",
        "_NET_WM_STATE_ABOVE",
        "_NET_WM_STATE_BELOW",
        "_NET_WM_STATE_DEMANDS_ATTENTION",
        "_NET_WM_STATE_FOCUSED"
};

/* some window struct */

typedef struct {

    Display *dpy;
    Window id;

    struct {
        Atom NET_WM_STATE;
        Atom NET_WM_STATES[WINDOW_STATE_SIZE];
    } atoms;

} window_t;

window_t win;

/* in window initialization function */

//win->atoms.NET_WM_STATE = XInternAtom(win->dpy, "_NET_WM_STATE", False);
//
//for (i=0; i < WINDOW_STATE_SIZE; ++i) {
//    win->atoms.NET_WM_STATES[i] = XInternAtom(win->dpy, WINDOW_STATE_NAMES[i], False);
//}
//
///* a function to retrieve the current state of the window */
//
//
//window_state_t get_window_state(window_t *win)
//{
//    long max_length = 1024;
//    Atom actual_type;
//    int actual_format;
//    unsigned long bytes_after, i, num_states = 0;
//    Atom* states = NULL;
//    window_state_t state = WINDOW_STATE_NONE;
//
//    if (XGetWindowProperty(win->dpy,
//                           win->id,
//                           win->atoms.NET_WM_STATE,
//                           0l,
//                           max_length,
//                           False,
//                           XA_ATOM,
//                           &actual_type,
//                           &actual_format,
//                           &num_states,
//                           &bytes_after,
//                           (unsigned char**) &states) == Success)
//    {
//        //for every state we get from the server
//        for (i = 0; i < num_states; ++i) {
//
//            //for every (known) state
//            for (int n=0; n < WINDOW_STATE_SIZE; ++n) {
//
//                //test the state at index i
//                if (states[i] == win->atoms.NET_WM_STATES[n]) {
//                    state |= (1 << n);
//                    break;
//                }
//
//            }
//
//        }
//
//        XFree(states);
//    }
//
//    return state;
//}
//int window_is_minimized(Display *display, Window window) {
//    Atom actual_type;
//    int actual_format;
//    unsigned long i, num_items, bytes_after;
//    Atom *atoms;
//
//    atoms=NULL;
//
//    XGetWindowProperty(display, window, vdl_x11_usefull_atoms->_NET_WM_STATE, 0, 1024, False, XA_ATOM, &actual_type, &actual_format, &num_items, &bytes_after, (unsigned char**)&atoms);
//
//    for(i=0; i<num_items; ++i) {
//        if(atoms[i]==vdl_x11_usefull_atoms->_NET_WM_STATE_HIDDEN) {
//            XFree(atoms);
//            return 1;
//        }
//    }
//    XFree(atoms);
//    return 0;
//}
//int xlibWinState() {
//
//}
int main2(int argc, char *argv[]) {
//    int x11ID = getX11ID(argc, argv);
//    assert(x11ID > 0);
//    printf("X11ID: %d \n", x11ID);

    gtk_init(&argc, &argv);

    // 获取窗口
    gint64 xid = 0x7200005;//g_ascii_strtoll(x11ID, NULL, 16);
    printf("xid: %d \n", xid);
//    GdkWindow *gdkWin = getGdkWin((xid));
//    checkWin(gdkWin);

//    checkWinXlib();
//    GdkWindowState state = gdk_window_get_state(gdkWin);
//    printf("state: %d\n", state);
//    printf("size of state: %ld\n", sizeof(state));

//    gdk_window_get_state(gdkWin);
//    gtk_widget_get_state(gtkWin);
//    gtk_widget_get_state_flags(gtkWin);
//    gtk_widget_get_parent_window(gtkWin);

//    debugSelfWin();
    gtk_main();
    return 0;
}

void checkWinByXlib() {
    XWindowAttributes *attr;
    Display *display;
    Window w;
    w = 0x7200005;
    XWindowAttributes *window_attributes_return;

    display = XOpenDisplay(":0");
    assert(display != NULL);
    XGetWindowAttributes(display, w, window_attributes_return);
    printf("%d \n", window_attributes_return);
}
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    checkWinByXlib();
    gtk_main();
    return 0;
}