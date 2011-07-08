/* vdesk: virtual desktops for any window manager     
 * Copyright 2001, 2003 Adam Sampson <azz@us-lot.org>
 * Originally based on code from aewm:
 * Copyright (c) 1998-2001 Decklin Foster.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS", WITHOUT ANY EXPRESS
 * OR IMPLIED WARRANTIES OF ANY KIND. IN NO EVENT SHALL THE AUTHOR BE
 * HELD LIABLE FOR ANY DAMAGES CONNECTED WITH THE USE OF THIS PROGRAM.
 * 
 * You are granted permission to copy, publish, distribute, and/or sell
 * copies of this program and any modified versions or derived works,
 * provided that this copyright and notice are not removed or altered.
 */

/*
 * changed some stuff.
 * (c) 2011 Any
 */

/*
 * destroyed vdesk() so I could use it inside libopencde.
 * done very badly and I imagine I made many bugs.
 * (c) 2011 Karsten
 */

enum { INVISIBLE, VISIBLE };

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <opencde.h>

Display *dpy;
Window root;
Atom wm_state, vdesk_desktop, wm_change_state, xa_INTTYP;
/* Start off the current desk at 1 so that we can set the root
   window correctly the first time we start up. */
long todesk, curdesk = 1;

int remap(Display * d, Window win);

void set_window_desk_vis(Window w, long n, long vis) {
    long buf[3];
    buf[0] = n; buf[1] = vis; 
    XChangeProperty(dpy, w, vdesk_desktop, xa_INTTYP, 32, PropModeReplace, 
        (unsigned char *)buf, 2);
}

long get_window_desk_vis(Window w, long *ovis) {
    Atom real_type; int real_format;
    unsigned long items_read, items_left;
    long *data, n = -1, vis = -1;

    if (XGetWindowProperty(dpy, w, vdesk_desktop, 0L, 2L, False,
            xa_INTTYP, &real_type, &real_format, &items_read, &items_left,
            (unsigned char **) &data) == Success && items_read) {
        n = data[0];
        vis = data[1];
        XFree(data);
    }
    if (n == -1) {
        /* If it's not set, make it the current desk and visible. */
        set_window_desk_vis(w, curdesk, VISIBLE);
        *ovis = 1;
        return curdesk;
    } else {
        *ovis = vis;
        return n;
    }
}

long get_wm_state(Window w, unsigned long int * ico)
{
    Atom real_type; int real_format;
    unsigned long items_read, items_left;
    long *data, state = -1;
    char * n;

    *ico = 0;
    if (XGetWindowProperty(dpy, w, wm_state, 0L, 2L, False,
            wm_state, &real_type, &real_format, &items_read, &items_left,
            (unsigned char **) &data) == Success && items_read) {
        state = *data;
    * ico = *(data + 1);
        XFree(data);
    }
    else if (XGetWindowProperty(dpy, w, vdesk_desktop, 0L, 2L, False,
            xa_INTTYP, &real_type, &real_format, &items_read, &items_left,
            (unsigned char **) &data) == Success && items_read) {
        /*
         * Client might reset WM_STATE when withdrawn.  Kde of course
         * does.  Thanks alot.
         */
        XFree(data);
        if ( w == root )
            return -1;  // if at first you don't succeed... cheat.
        state = WithdrawnState;
    }
    return state;
}

void on_clients(Window w) {
    Window dummy_w, *wins;
    unsigned int i, nwins;
    unsigned long int sticky, ico;

    long state = get_wm_state(w, &ico);

    if (state != -1) {
        long vis, n;
        n = get_window_desk_vis(w, &vis);

        if (state == NormalState) {
            /* If the window isn't sticky, changing desktops will
               always hide it. */
            if (n) {
                /* Since it was visible, it's been moved behind our back
                   and should really be on this desktop. */
                set_window_desk_vis(w, curdesk, VISIBLE);

                /* And hide it. */
                XWithdrawWindow (dpy, w, DefaultScreen (dpy));
            }
        } else if (state == WithdrawnState){
            if (n == curdesk) {
                /* Invisible, but on the current desktop -- means
                   it's been iconified. */
                set_window_desk_vis(w, curdesk, INVISIBLE); 
            } else if (n == todesk && vis == VISIBLE) {
                remap(dpy, w);
            }
        }
# if 0
    else if (state == -2) {

    }
# endif
        else  {
            if (ico && n == curdesk) {
                set_window_desk_vis(w, curdesk, INVISIBLE); 
                XWithdrawWindow (dpy, ico, DefaultScreen (dpy));
            }
            else if (ico && n == todesk) {
                remap(dpy, w);
                XIconifyWindow(dpy, w, DefaultScreen (dpy));
            }
    }

    } else if (XQueryTree(dpy, w, &dummy_w, &dummy_w, &wins, &nwins)) {
        for (i = 0; i < nwins; i++)
            on_clients(wins[i]);
        XFree(wins);
    }
}

int remap(Display * d, Window win){
    Window root;
    int x, y;
    unsigned int w, h, border, depth;
    Status st;
    
    /*
     *  Map in and fix windowpositions.  Works for all but kde.
     *  which loses geometry on withdrawing.  Probably for a reason.
     */

    XGetGeometry(dpy, win, &root, &x, &y, &w, &h, &border, &depth);
    XMapWindow(dpy, win);
    XMoveWindow(dpy, win, x, y);


    return 0;
}


void usage() {
    exit(1);
}



int vdesk(int argc, Window winId, int deskNo) {
    long t, throwaway;
    unsigned long ico;
    int change = 0;
    const char* argv[3];

    argv[0] = "Workspace";
    argv[1] = "Workspace";
    argv[2] = "Workspace";

		//std::cout << argv[0] << std::endl;
		//std::cout << argv[1] << std::endl;
		//std::cout << argv[2] << std::endl;
    opterr = 0;

/*
    while (1) {
        int c = getopt(argc, argv, "+?");
        if (c == -1)
            break;

        usage();
    }
*/

    dpy = XOpenDisplay(NULL);   // FIXME!  
    if (!dpy) {
        fprintf(stderr, "%s: cannot open display\n", argv[0]);
        exit(2);
    }

    wm_state = XInternAtom(dpy, "WM_STATE", False);
    vdesk_desktop = XInternAtom(dpy, "VDESK_DESKTOP", False);
    wm_change_state = XInternAtom(dpy, "WM_CHANGE_STATE", False);
    xa_INTTYP = XInternAtom(dpy, "INTEGER", False);
    root = DefaultRootWindow(dpy);
    curdesk = get_window_desk_vis(root, &t);

    if (0 == argc) {
        /* Print the current desktop number. */
        printf("%ld\n", curdesk);
        return 0;
    }

    //if ((argc - optind) == 1)
    //    change = 1;

    if(argc == 2)
    {
      change = 1;
    }
    else
    {
      change = 0;
    }

    //todesk = strtol(argv[optind], NULL, 0);
    //std::cout << deskNo << std::endl;
    todesk = deskNo;
    if (todesk < 0 || (change && todesk == 0)) {
        //fprintf(stderr, "%s: bad desktop number '%s'\n", argv[0], argv[optind]);
        //usage();
      return 0;
    }
    ++optind;

    if (change) {
        /* Switch to the given desktop. */
        if (todesk != curdesk) {
            XGrabServer(dpy);
            on_clients(root);
            set_window_desk_vis(root, todesk, VISIBLE);
            XUngrabServer(dpy);
        }
    } else {
        /* Move the given windows to the given desktop. */
        Window w;
        int i;

        for (i = 0; i < 1; i++) {
            //w = strtol(argv[i], NULL, 0);
            w = winId;

		//std::cout << w << std::endl;

            if (w) {
                int is_visible = get_wm_state(w, &ico) == NormalState;

                set_window_desk_vis(w, todesk, is_visible);
                if (!is_visible && (todesk == curdesk || !todesk)) {
                    remap(dpy, w);
                }
                if (is_visible && todesk && todesk != curdesk) {
                    XWithdrawWindow (dpy, w, DefaultScreen (dpy));
                }
            } else {
		// fix... no longer use arg[]
                fprintf(stderr, "%s: bad window id '%s'\n", argv[0], argv[i]);
                usage();
            }
        }
    }

    XFlush(dpy);
    XCloseDisplay(dpy);
    return 0;
}

