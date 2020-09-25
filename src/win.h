#include "scene.h"

#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>


class Canvas
{
	public:
	Window window;
	Display *dpy;
	GC gc;
	int screen;
	int blackColor;// = BlackPixel(dpy, DefaultScreen(dpy));
    int whiteColor;// = WhitePixel(dpy, DefaultScreen(dpy));

	Canvas();

	void Drawpixel(jdscn::Position2D pos);
};


