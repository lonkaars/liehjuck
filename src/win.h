#pragma once
#include "jdscn_types.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <memory>

namespace Win
{

class Canvas
{
	public:
	std::vector<char> emptydata;
	int width;
	int height;
	const char *title;
	
	Display *dpy;
	Window win;
	GC gc;
	XImage *frame;

	Canvas();
	Canvas(int, int, const char *);
	void draw(int, int, jdscn::Color);
	void flush();
	void clear();
};

}; // namespace Win
