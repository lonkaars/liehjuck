#include "win.h"
#include "../lib/gfx/gfx.h"
#include "scene.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

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
	gfx_open(width, height, title);
}

void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;
	gfx_color(c[0], c[1], c[2]);
	gfx_point(x, y);
}

void Canvas::clear()
{
	gfx_clear();
}

}; // namespace Win
