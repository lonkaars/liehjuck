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

Canvas::Canvas(int width, int height, const char *title) { gfx_open(width, height, title); }

void Canvas::draw(int x, int y, jdscn::Color c)
{
	gfx_color(c[0], c[1], c[2]);
	gfx_point(x, y);
}

}; // namespace Win
