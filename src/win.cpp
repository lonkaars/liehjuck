#include "scene.h"
#include "win.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>
#include <iostream>

Canvas::Canvas()
{
	dpy = XOpenDisplay(NULL);


	blackColor = BlackPixel(dpy, DefaultScreen(dpy));
	whiteColor = WhitePixel(dpy, DefaultScreen(dpy));
	window =  XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 
				     1280, 720, 0, blackColor, blackColor);
	gc = XCreateGC(dpy, window, 0, NULL);
 	XSelectInput(dpy, window, StructureNotifyMask);
	XMapWindow(dpy, window);
	
	for(;;) {
	    XEvent e;
	    XNextEvent(dpy, &e);
	    if (e.type == MapNotify)
		  break;
    }

	XSetForeground(dpy, gc, whiteColor);
	//sleep(10);
}

void Canvas::Drawpixel(jdscn::Position2D pos)
{
	XSetForeground(dpy, gc, whiteColor);
	XDrawPoint(dpy, window, gc, pos[0], pos[1]);
	XFlush(dpy);
}

