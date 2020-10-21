#pragma once
#include "jdscn_types.h"
#include <X11/Xlib.h>

/** @file win.h */

/**
 * @brief Handles all X11 drawing
 */
namespace Win
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
	Display *display;
	Window window;
	GC gc;
	Colormap colormap;

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

}; // namespace Win
