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

namespace win
{
Canvas::Canvas() {}

Canvas::Canvas(int width, int height, const char *title)
	: emptydata( width * height * 4, 0 )
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

	XStoreName(dpy, win, title);

	XSelectInput(dpy, win, StructureNotifyMask | KeyPressMask | ButtonPressMask);

	XMapWindow(dpy, win);

	gc = XCreateGC(dpy, win, 0, 0);

	// Wait for the MapNotify event

	for (;;) {
		XEvent e;
		XNextEvent(dpy, &e);
		if (e.type == MapNotify)
			break;
	}
	
	frame = XCreateImage(dpy, DefaultVisual(dpy, DefaultScreen(dpy)), 24, ZPixmap, 0, (char *) emptydata.data(), width, height, 32, width * 4);	
}

// Draws a pixel at given x and y coordinates in the color that is specified in c
void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;

	int color = c[2] + c[1] * 256 + c[0] * 256 * 256;
	XPutPixel(frame, x, y, color);
}

// Sends the stored frame to the x server
void Canvas::flush()
{
	XPutImage(dpy, win, gc, frame, 0, 0, 0, 0, width, height);
}

// Writes the frame data to just zeroes
// Using memset isn't the most beautiful way to do this, but other methods cause headaches
void Canvas::clear()
{
	const size_t data_size = frame->bytes_per_line * frame->height;
	memset(frame->data, 0, data_size);	
}

}; // namespace win
