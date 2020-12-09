#pragma once
#include "jdscn_types.h"
#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

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
	xcb_image_t *frame;
	
	std::vector<float> depthframe;

	uint32_t mask;

	/**
	 * @brief Initialize a window to draw on
	 *
	 * @param width window width
	 * @param height window height
	 * @param title window title
	 */
	Canvas(int, int, const char *);
	/**
	 * @brief Draws a pixel with a specific color to `frame`
	 *
	 * @param int x coordinate
	 * @param int y coordinate
	 * @param jdscn::Color color
	 */
	void draw(jdscn::Position, jdscn::Color);
	/**
	 * @brief Draws from the top-left (absolute coordinates)
	 *
	 * @param int x coordinate
	 * @param int y coordinate
	 * @param jdscn::Color color
	 */
	void drawAbsolute(int, int, jdscn::Color);
	/** @brief Draws `frame` to the window */
	void flush();
	/** @brief Clears the canvas */
	void clear();

	/**
	 * @brief Draws a line between two points in a specific color to a canvas
	 *
	 * @param jdscn::Position2D Starting point of line
	 * @param jdscn::Position2D Ending point of line
	 * @param jdscn::Color Color for line
	 * @param win::Canvas& Canvas to draw the line on
	 */
	void line(jdscn::Position, jdscn::Position, jdscn::Color);
	/**
	 * @brief Draws a triangle between 3 points
	 *
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::Color Color of triangle
	 */
	void drawTriangle(jdscn::Tri, jdscn::Color);

	jdscn::Position convertToAbsolute(jdscn::Position);
	/**
	 * @brief Draws a filled triangle between 3 points
	 *
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::FloatXY Point of triangle
	 * @param jdscn::Color color of triangle
	 */
	void drawFilledTriangle(jdscn::Tri, jdscn::Color);
	/**
	 * @brief Draws a line without gaps by changing the scanline axis
	 *
	 * @param jdscn::Position2D start point
	 * @param jdscn::Position2D end point
	 * @param jdscn::Color line color
	 */
	void prettyLine(jdscn::Position2D, jdscn::Position2D, jdscn::Color);
};

}; // namespace win
