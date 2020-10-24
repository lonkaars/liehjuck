#pragma once
#include "jdscn_types.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <xcb/xcb.h>

/** @file win.h */

/** @brief Manages an X11 window */
namespace win
{

/** @brief Manages the window and exposes simple drawing functions */
class Canvas
{
	public:
	std::vector<char> emptydata;
	int width;
	int height;
	const char *title;

	/** @brief connection to the x server */
	xcb_connection_t *connection;
	/** @brief current display */
	xcb_screen_t *display;
	/** @brief current window */
	xcb_window_t window;
	/** @brief graphics context */
	xcb_gcontext_t gc;
	/** @brief bitmap for drawing */
	xcb_pixmap_t frame;
	uint32_t mask;

	Canvas(int, int, const char *);
	/**
	 * @brief Draws a pixel with a specific color to `frame`
	 *
	 * @param int x coordinate
	 * @param int y coordinate
	 * @param jdscn::Color color
	 */
	void draw(int, int, jdscn::Color);
	/** @brief Draws `frame` to the window */
	void flush();
	/** @brief Clears the canvas */
	void clear();
};

}; // namespace win
