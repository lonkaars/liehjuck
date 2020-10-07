#pragma once
#include "../lib/gfx/gfx.h"
#include "jdscn_types.h"
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>

namespace Win
{

class Canvas
{
	public:
	int width;
	int height;
	const char *title;
	Canvas(int, int, const char *);
	void draw(int, int, jdscn::Color);
	void clear();
};

}; // namespace Win
