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

/** @file win.h */

/**
 * @brief Handles all X11 drawing
 */
namespace win
{

/**
 * @brief Manages the window and exposes simple drawing functions
 */
class Canvas
{
	public:
	int width;
	int height;
	const char *title;
	Canvas();
	Canvas(int, int, const char *);
	/**
	 * @brief Draws a pixel with a specific color to the canvas
	 *
	 * @param int x coordinate
	 * @param int y coordinate
	 * @param jdscn::Color color
	 */
	void draw(int, int, jdscn::Color);
	/**
	 * @brief Clears the canvas
	 */
	void clear();
};

}; // namespace win
