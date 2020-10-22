#include "win.h"
#include "scene.h"
#include <X11/Xlib.h>
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

Canvas::Canvas(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	display = XOpenDisplay(0);
	if (!display) {
		fprintf(stderr, "unable to open the graphics window.\n");
		exit(1);
	}

	int blackColor = BlackPixel(display, DefaultScreen(display));
	int whiteColor = WhitePixel(display, DefaultScreen(display));

	window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, width, height, 0,
								 blackColor, blackColor);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(display, window, CWBackingStore, &attr);

	XStoreName(display, window, title);

	XSelectInput(display, window, StructureNotifyMask | KeyPressMask | ButtonPressMask);

	XMapWindow(display, window);

	gc = XCreateGC(display, window, 0, 0);

	colormap = DefaultColormap(display, 0);

	XSetForeground(display, gc, whiteColor);

	for (;;) {
		XEvent e;
		XNextEvent(display, &e);
		if (e.type == MapNotify)
			break;
	}
	
	frame = XCreateImage(display, DefaultVisual(display, DefaultScreen(display)), 24, ZPixmap, 0, (char *) emptydata.data(), width, height, 32, width * 4);	
}

// Draws a pixel at given x and y coordinates in the color that is specified in c
void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;

	if(x > this->width ||
	   x < 0 ||
	   y > this->height ||
	   y < 0) return;

	int color = c[2] + c[1] * 256 + c[0] * 256 * 256;
	XPutPixel(frame, x, y, color);
}

// Sends the stored frame to the x server
void Canvas::flush()
{
	XPutImage(display, window, gc, frame, 0, 0, 0, 0, width, height);
}

// Writes the frame data to just zeroes
// Using memset isn't the most beautiful way to do this, but other methods cause headaches
void Canvas::clear()
{
	const size_t data_size = frame->bytes_per_line * frame->height;
	memset(frame->data, 0, data_size);	
}

}; // namespace win
