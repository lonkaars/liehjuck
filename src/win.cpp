#include "win.h"
#include "scene.h"
#include <X11/Xlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sys/utsname.h>

namespace Win
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
}

void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;

	XColor color;
	color.pixel = ((c[2] & 0xff) | ((c[1] & 0xff) << 8) | ((c[0] & 0xff) << 16));
	XSetForeground(this->display, this->gc, color.pixel);

	XDrawPoint(this->display, this->window, this->gc, x, y);
}

void Canvas::clear() { XClearWindow(this->display, this->window); }

}; // namespace Win
