#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <chrono>


static Display *gfx_display = 0;
static Window gfx_window;
static GC gfx_gc;
static Colormap gfx_colormap;
static int gfx_fast_color_mode = 0;
static XImage *bg;

static int saved_xpos = 0;
static int saved_ypos = 0;
int main()
{
	int width = 800;
	int height = 600;
	const char *title = "bitmap-test";

	gfx_display = XOpenDisplay(0);
	if (!gfx_display) {
		fprintf(stderr, "gfx_open: unable to open the graphics window.\n");
		exit(1);
	}

	int blackColor = BlackPixel(gfx_display, DefaultScreen(gfx_display));
	int whiteColor = WhitePixel(gfx_display, DefaultScreen(gfx_display));

	gfx_window = XCreateSimpleWindow(gfx_display, DefaultRootWindow(gfx_display), 0, 0, width,
									 height, 0, blackColor, blackColor);

	XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(gfx_display, gfx_window, CWBackingStore, &attr);

	XStoreName(gfx_display, gfx_window, title);

	XSelectInput(gfx_display, gfx_window, StructureNotifyMask | KeyPressMask | ButtonPressMask);

	XMapWindow(gfx_display, gfx_window);

	gfx_gc = XCreateGC(gfx_display, gfx_window, 0, 0);

	gfx_colormap = DefaultColormap(gfx_display, 0);

	XSetForeground(gfx_display, gfx_gc, whiteColor);
	
	// Wait for the MapNotify event

	for (;;) {
		XEvent e;
		XNextEvent(gfx_display, &e);
		if (e.type == MapNotify)
			break;
	}
	
	XDrawPoint(gfx_display, gfx_window, gfx_gc, 1, 1);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	bg = XGetImage(gfx_display, gfx_window, 0, 0, 2, 2, AllPlanes, ZPixmap);
	
	std::cout << "test";
	std::cout << bg->data[9];	
	XPutImage(gfx_display, gfx_window, gfx_gc, bg, 0, 0, 0, 0, width, height);
	std::this_thread::sleep_for(std::chrono::seconds(20));
}
