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
#include <algorithm>
#include <iterator>

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
	emptyframe = XGetImage(dpy, win, 0, 0, width, height, AllPlanes, ZPixmap);
}

void Canvas::draw(int x, int y, jdscn::Color c)
{
	XPutPixel(frame, x, y, c[2] + c[1] * 256 + c[2] * 256 * 256);
}

void Canvas::flush()
{
	XPutImage(dpy, win, gc, frame, 0, 0, 0, 0, width, height);
}

void Canvas::clear()
{
	// copy the image data from emptyframe to frame
	const size_t data_size = frame->bytes_per_line * frame->height;
	memcpy(frame->data, emptyframe->data, data_size);
}

}; // namespace Win
