#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdio.h>
#include <errno.h>   // for errno
#include <limits.h>  // for INT_MAX, INT_MIN
#include <stdlib.h>  // for strtol
#include <assert.h>  // for assert
#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
#include <unistd.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <X11/cursorfont.h>

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

//void checkWinByXlib() {
//    XWindowAttributes *attr;
//    Display *display = NULL;
//    Window w;
//    w = 0x7200005;
//    XWindowAttributes window_attributes_return;
//
//    display = XOpenDisplay(":0");
//    assert(display != NULL);
//    int status;
//    status = XGetWindowAttributes(display, w, &window_attributes_return);
//
//    printf("%d \n", status);
//    printf("%d \n", window_attributes_return);
//    printf("%s \n", window_attributes_return.width);
//    printf("%s \n", window_attributes_return.height);
//    printf("%s \n", window_attributes_return.x);
//    printf("%s \n", window_attributes_return.y);
//    printf("%s \n", window_attributes_return.map_state);
//
//    XCloseDisplay(display);
//}




enum {
    /* xcb_size_hints_flags_t */
    XCB_ICCCM_SIZE_HINT_US_POSITION = 1 << 0,
    XCB_ICCCM_SIZE_HINT_US_SIZE = 1 << 1,
    XCB_ICCCM_SIZE_HINT_P_POSITION = 1 << 2,
    XCB_ICCCM_SIZE_HINT_P_SIZE = 1 << 3,
    XCB_ICCCM_SIZE_HINT_P_MIN_SIZE = 1 << 4,
    XCB_ICCCM_SIZE_HINT_P_MAX_SIZE = 1 << 5,
    XCB_ICCCM_SIZE_HINT_P_RESIZE_INC = 1 << 6,
    XCB_ICCCM_SIZE_HINT_P_ASPECT = 1 << 7,
    XCB_ICCCM_SIZE_HINT_BASE_SIZE = 1 << 8,
    XCB_ICCCM_SIZE_HINT_P_WIN_GRAVITY = 1 << 9,
    /* xcb_wm_state_t */
    XCB_ICCCM_WM_STATE_WITHDRAWN = 0,
    XCB_ICCCM_WM_STATE_NORMAL = 1,
    XCB_ICCCM_WM_STATE_ICONIC = 3,
    /* xcb_wm_t */
    XCB_ICCCM_WM_HINT_INPUT = (1L << 0),
    XCB_ICCCM_WM_HINT_STATE = (1L << 1),
    XCB_ICCCM_WM_HINT_ICON_PIXMAP = (1L << 2),
    XCB_ICCCM_WM_HINT_ICON_WINDOW = (1L << 3),
    XCB_ICCCM_WM_HINT_ICON_POSITION = (1L << 4),
    XCB_ICCCM_WM_HINT_ICON_MASK = (1L << 5),
    XCB_ICCCM_WM_HINT_WINDOW_GROUP = (1L << 6),
    XCB_ICCCM_WM_HINT_X_URGENCY = (1L << 8)
};
typedef struct {
    /** User specified flags */
    uint32_t flags;
    /** User-specified position */
    int32_t x, y;
    /** User-specified size */
    int32_t width, height;
    /** Program-specified minimum size */
    int32_t min_width, min_height;
    /** Program-specified maximum size */
    int32_t max_width, max_height;
    /** Program-specified resize increments */
    int32_t width_inc, height_inc;
    /** Program-specified minimum aspect ratios */
    int32_t min_aspect_num, min_aspect_den;
    /** Program-specified maximum aspect ratios */
    int32_t max_aspect_num, max_aspect_den;
    /** Program-specified base size */
    int32_t base_width, base_height;
    /** Program-specified window gravity */
    uint32_t win_gravity;
} wm_size_hints_t;
# define xcb_size_hints_t wm_size_hints_t
struct wininfo {
    xcb_window_t			window;

    /* cookies for requests we've sent */
    xcb_get_geometry_cookie_t		geometry_cookie;
    xcb_get_property_cookie_t		net_wm_name_cookie;
    xcb_get_property_cookie_t		wm_name_cookie;
    xcb_get_property_cookie_t		wm_class_cookie;
    xcb_translate_coordinates_cookie_t	trans_coords_cookie;
    xcb_query_tree_cookie_t		tree_cookie;
    xcb_get_window_attributes_cookie_t	attr_cookie;
    xcb_get_property_cookie_t		normal_hints_cookie;
    xcb_get_property_cookie_t		hints_cookie;
    xcb_get_property_cookie_t		wm_desktop_cookie;
    xcb_get_property_cookie_t		wm_window_type_cookie;
    xcb_get_property_cookie_t		wm_state_cookie;
    xcb_get_property_cookie_t		wm_pid_cookie;
    xcb_get_property_cookie_t		wm_client_machine_cookie;
    xcb_get_property_cookie_t		frame_extents_cookie;
    xcb_get_property_cookie_t		zoom_cookie;

    /* cached results from previous requests */
    xcb_get_geometry_reply_t *		geometry;
    xcb_get_window_attributes_reply_t *	win_attributes;
    xcb_size_hints_t *			normal_hints;
};
# define GET_TEXT_PROPERTY(Dpy, Win, Atom) \
    xcb_get_property (Dpy, False, Win, Atom, XCB_GET_PROPERTY_TYPE_ANY, 0, BUFSIZ)
# define xcb_icccm_get_wm_name(Dpy, Win) \
    GET_TEXT_PROPERTY(Dpy, Win, XCB_ATOM_WM_NAME)
static xcb_get_property_cookie_t get_net_wm_name (xcb_connection_t *,
                                                  xcb_window_t);
typedef struct {
    /** Marks which fields in this structure are defined */
    int32_t flags;
    /** Does this application rely on the window manager to get keyboard
        input? */
    uint32_t input;
    /** See below */
    int32_t initial_state;
    /** Pixmap to be used as icon */
    xcb_pixmap_t icon_pixmap;
    /** Window to be used as icon */
    xcb_window_t icon_window;
    /** Initial position of icon */
    int32_t icon_x, icon_y;
    /** Icon mask bitmap */
    xcb_pixmap_t icon_mask;
    /* Identifier of related window group */
    xcb_window_t window_group;
} wm_hints_t;
#define xcb_icccm_wm_hints_t wm_hints_t
static xcb_atom_t atom_net_wm_name, atom_utf8_string;
static Bool window_id_format_dec = False;
static void print_utf8 (const char *, const char *, size_t, const char *);

static const char *
window_id_str (xcb_window_t id)
{
    static char str[20];

    if (window_id_format_dec)
        snprintf (str, sizeof(str), "%u", id);
    else
        snprintf (str, sizeof(str), "0x%x", id);

    return str;
}
struct atom_cache_entry {
    xcb_atom_t atom;
    const char *name;
    xcb_intern_atom_cookie_t intern_atom;
    struct atom_cache_entry *next;
};
static struct atom_cache_entry *atom_cache;
/*
 * Send a request to the server for an atom by name
 * Does not create the atom if it is not already present
 */
struct atom_cache_entry *Intern_Atom (xcb_connection_t * dpy, const char *name)
{
    struct atom_cache_entry *a;

    for (a = atom_cache ; a != NULL ; a = a->next) {
        if (strcmp (a->name, name) == 0)
            return a; /* already requested or found */
    }

    a = calloc(1, sizeof(struct atom_cache_entry));
    if (a != NULL) {
        a->name = name;
        a->intern_atom = xcb_intern_atom (dpy, False, strlen (name), (name));
        a->next = atom_cache;
        atom_cache = a;
    }
    return a;
}


/* Get an atom by name when it is needed. */
xcb_atom_t Get_Atom (xcb_connection_t * dpy, const char *name)
{
    struct atom_cache_entry *a = Intern_Atom (dpy, name);

    if (a == NULL)
        return XCB_ATOM_NONE;

    if (a->atom == XCB_ATOM_NONE) {
        xcb_intern_atom_reply_t *reply;

        reply = xcb_intern_atom_reply(dpy, a->intern_atom, NULL);
        if (reply) {
            a->atom = reply->atom;
            free (reply);
        } else {
            a->atom = (xcb_atom_t) -1;
        }
    }
    if (a->atom == (xcb_atom_t) -1) /* internal error */
        return XCB_ATOM_NONE;

    return a->atom;
}

int checkWinByXCB2() {
    xcb_icccm_wm_hints_t wmhints;
    long flags;
    char *display_name = ":0";
    Display *dpy = XOpenDisplay(display_name);
    xcb_connection_t *c;
    const xcb_setup_t *setup;
    xcb_screen_t *screen;
    xcb_window_t window;

//    const int depth = 0, x = 0, y = 0, width = 150, height = 150,
//            border_width = 1;

    if (! dpy)
    {
        fprintf(stderr, "Could not open display.\n");
        exit(EXIT_FAILURE);
    }

    c = XGetXCBConnection(dpy);

    if (! c)
    {
        fprintf(stderr, "Could not cast the Display object to an "
                        "XCBConnection object.\n");
        exit(EXIT_FAILURE);
    }

    /* Do something meaningful, fun, and interesting with the new
     * XCBConnection object.
     */
//    setup  = xcb_get_setup (c);
//    screen = (xcb_setup_roots_iterator (setup)).data;
//    window = xcb_generate_id (c);
//    window = xcb_get_property()
//    xcb_window_
//    xcb_create_window (c, depth, window, screen->root, x, y, width, height,
//                       border_width, InputOutput, screen->root_visual, 0, NULL);
//    xcb_map_window (c, window);

//    xcb_flush (c);

//    pause();

//    return EXIT_SUCCESS;


    xcb_get_property_reply_t *prop;
    int i;
    int frame = 0, children = 0;
    struct wininfo wininfo;
    struct wininfo *w = &wininfo;
    memset (w, 0, sizeof(struct wininfo));
    static atom_net_wm_state;
    xcb_atom_t atom_wm_state = XCB_ATOM_NONE;

    window = strtoul(0x7600006, NULL, 0);
    /* If no window selected on command line, let user pick one the hard way */
    if (!window) {
        Intern_Atom (dpy, "_NET_VIRTUAL_ROOTS");
        Intern_Atom (dpy, "WM_STATE");
    }
    atom_wm_state = Get_Atom(dpy, "WM_STATE");
    printf("%s", atom_wm_state);
    atom_net_wm_state = Get_Atom (dpy, "_NET_WM_STATE");
    printf("%s", atom_net_wm_state);
//    if (atom_net_wm_state) {
//        w->wm_state_cookie = xcb_get_property
//                (dpy, False, window, atom_net_wm_state,
//                 XCB_ATOM_ATOM, 0, BUFSIZ);
//    }
//    if (atom_net_wm_state) {
//        prop = xcb_get_property_reply(dpy, w->wm_state_cookie, NULL);
//        if (prop && (prop->type != XCB_NONE) && (prop->value_len > 0)) {
//            xcb_atom_t *atoms = xcb_get_property_value(prop);
//            int atom_count = prop->value_len;
//
//            if (atom_count > 0) {
//                printf("      Window state:\n");
//                for (i = 0; i < atom_count; i++)
//                    Display_Atom_Name(atoms[i], "_NET_WM_STATE_");
//            }
//        }
//    }
}






xcb_atom_t getatom(xcb_connection_t* c, char *atom_name)
{
    xcb_intern_atom_cookie_t atom_cookie;
    xcb_atom_t atom;
    xcb_intern_atom_reply_t *rep;

    atom_cookie = xcb_intern_atom(c, 0, strlen(atom_name), atom_name);
    rep = xcb_intern_atom_reply(c, atom_cookie, NULL);
    if (NULL != rep)
    {
        atom = rep->atom;
        free(rep);
        printf("\natom: %ld",atom);
        fflush(stdout);
        return atom;
    }
    printf("\nError getting atom.\n");
    exit(1);
}

void checkWinByXCB3() {

    xcb_generic_error_t *e;
    int i,j,k;

    xcb_connection_t* c = xcb_connect(NULL, NULL);
    xcb_atom_t net_client_list = getatom(c,"_NET_CLIENT_LIST");
    xcb_atom_t net_wm_visible_name = getatom(c,"_NET_WM_VISIBLE_NAME");

    xcb_screen_t* screen = xcb_setup_roots_iterator(xcb_get_setup(c)).data;

    xcb_get_property_cookie_t prop_cookie_list,prop_cookie;
    xcb_get_property_reply_t *reply_prop_list,*reply_prop;

    prop_cookie_list = xcb_get_property(c, 0, screen->root, net_client_list, XCB_GET_PROPERTY_TYPE_ANY, 0, 100);
    reply_prop_list = xcb_get_property_reply(c, prop_cookie_list, &e);
    if(e) {
        printf("\nError: %d",e->error_code);
        free(e);
    }
    if(reply_prop_list) {
        int value_len = xcb_get_property_value_length(reply_prop_list);
        printf("\nvalue_len: %d",value_len);
        if(value_len) {
            xcb_window_t* win = xcb_get_property_value(reply_prop_list);
            for(i=0; i<value_len; i++) {
                printf("\n--------------------------------\nwin id: %d",win[i]);
                prop_cookie = xcb_get_property(c, 0, win[i], net_wm_visible_name, XCB_GET_PROPERTY_TYPE_ANY, 0, 1000);
                reply_prop = xcb_get_property_reply(c, prop_cookie, &e);
                if(e) {
                    printf("\nError: %d",e->error_code);
                    free(e);
                }
                if(reply_prop) {
                    int value_len2 = xcb_get_property_value_length(reply_prop);
                    printf("\nvalue_len2: %d",value_len2);
                    if(value_len2) {
                        char* name = malloc(value_len2+1);
                        strncpy(name,xcb_get_property_value(reply_prop),value_len2);
                        name[value_len2] = '\0';
                        printf("\nName: %s",name);
                        fflush(stdout);
                        free(name);
                    }
                    free(reply_prop);
                }
            }
        }
        free(reply_prop_list);
    }
    printf("\n\n");
    fflush(stdout);
    exit(0);
}
int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
//    checkWinByXCB2();
    checkWinByXCB3();
    gtk_main();
    return 0;
}
/** Send request to get a window state (WM_STATE).
 * \param w A client window.
 * \return The cookie associated with the request.
 */
//xcb_get_property_cookie_t
//xwindow_get_state_unchecked(xcb_window_t w)
//{
//    return xcb_get_property_unchecked(globalconf.connection, false, w, WM_STATE,
//                                      WM_STATE, 0L, 2L);
//}

/** Get a window state (WM_STATE).
 * \param cookie The cookie.
 * \return The current state of the window, or 0 on error.
 */
//uint32_t
//xwindow_get_state_reply(xcb_get_property_cookie_t cookie)
//{
//    /* If no property is set, we just assume a sane default. */
//    uint32_t result = XCB_ICCCM_WM_STATE_NORMAL;
//    xcb_get_property_reply_t *prop_r;
//
//    if((prop_r = xcb_get_property_reply(globalconf.connection, cookie, NULL)))
//    {
//        if(xcb_get_property_value_length(prop_r))
//            result = *(uint32_t *) xcb_get_property_value(prop_r);
//
//        p_delete(&prop_r);
//    }
//
//    return result;
//}