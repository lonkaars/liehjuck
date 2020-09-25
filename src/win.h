#pragma once
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

class Canvas
{
	public:
	Canvas(int, int, const char *);
	void draw(int, int, jdscn::Color);
};

}; // namespace Win
