#include "win.h"
#include "scene.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sys/utsname.h>
#include <thread>
#include <chrono>

namespace Win
{
Canvas::Canvas() {}

Canvas::Canvas(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	dpy = XOpenDisplay(0);
	if (!dpy) {
		std::cout << "Cant open window\n";
		exit(1);
	}

	int blackColor = BlackPixel(dpy, DefaultScreen(dpy));
	int whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

	win = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, width, height, 0, blackColor, blackColor);

	XSelectInput(dpy, win, StructureNotifyMask | KeyPressMask | ButtonPressMask);

	XMapWindow(dpy, win);

	gc = XCreateGC(dpy, win, 0, 0);

	XSetForeground(dpy, gc, whiteColor);
	
	// Wait for the MapNotify event

	for (;;) {
		XEvent e;
		XNextEvent(dpy, &e);
		if (e.type == MapNotify)
			break;
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(1));

	frame = XGetImage(dpy, win, 0, 0, width, height, AllPlanes, ZPixmap);
}

void Canvas::draw(int x, int y, jdscn::Color c)
{
	frame->data[3 * (x + width * y)] = WhitePixel(dpy, DefaultScreen(dpy));
	frame->data[3 * (x + width * y) + 1] = WhitePixel(dpy, DefaultScreen(dpy));
	frame->data[3 * (x + width * y) + 2] = WhitePixel(dpy, DefaultScreen(dpy));
}

void Canvas::flush()
{
	XPutImage(dpy, win, gc, frame, 0, 0, 0, 0, width, height);
}

void Canvas::clear()
{/* gfx_clear();*/ 

}

}; // namespace Win
