#pragma once
#include "jdscn_types.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <memory>
#include <xcb/xcb.h>

/** @file win.h */

/** @brief Handles all X11 drawing */
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

	/* Display *display; */
	/* Window window; */
	/* GC gc; */
	/* Colormap colormap; */
	xcb_connection_t *connection;
	xcb_screen_t *display;
	xcb_window_t window_id;
	xcb_void_cookie_t window;
	uint32_t gc_id;
	xcb_void_cookie_t gc;
	xcb_pixmap_t frame_id;
	xcb_void_cookie_t frame;

	Canvas(int, int, const char *);
	/**
	 * @brief Draws a pixel with a specific color to the canvas
	 *
	 * @param int x coordinate
	 * @param int y coordinate
	 * @param jdscn::Color color
	 */
	void draw(int, int, jdscn::Color);
	void flush();
	/**
	 * @brief Clears the canvas
	 */
	void clear();
};

}; // namespace win
