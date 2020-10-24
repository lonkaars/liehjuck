#include "win.h"
#include "scene.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <thread>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_pixel.h>

namespace win
{

Canvas::Canvas(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	connection = xcb_connect(NULL, NULL);
	display = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	window = xcb_generate_id(connection);

	uint32_t rgb = 0xff000000;

	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[2] = {display->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
													XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_POINTER_MOTION};

	gc = xcb_generate_id(connection);
	xcb_create_gc(connection, gc, display->root, XCB_GC_FOREGROUND, &rgb);

	xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, display->root, 0, 0, width, height,
					  0, XCB_WINDOW_CLASS_INPUT_OUTPUT, display->root_visual, mask, values);

	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME,
						XCB_ATOM_STRING, 8, strlen(title), title);

	frame = xcb_generate_id(connection);
	xcb_create_pixmap(connection, 24, frame, window, width, height);

	xcb_map_window(connection, window);

	xcb_flush(connection);

	xcb_generic_event_t *event;
	while ((event = xcb_wait_for_event(connection))) {
		if (event->response_type == XCB_EXPOSE)
			break;
		free(event);
	}
}

// Draws a pixel at given x and y coordinates in the color that is specified in c
void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;

	if (x > this->width || x < 0 || y > this->height || y < 0)
		return;

	int32_t rgb =
		pow(0x100, 3) + c[0] * pow(0x100, 2) + c[1] * pow(0x100, 1) + c[2] * pow(0x100, 0);
	xcb_point_t point[] = {{int16_t(x), int16_t(y)}};
	xcb_change_gc(connection, gc, XCB_GC_FOREGROUND, &rgb);
	xcb_poly_point(connection, XCB_COORD_MODE_ORIGIN, frame, gc, 1, point);
}

// Sends the stored frame to the x server
void Canvas::flush()
{
	xcb_copy_area(connection, frame, window, gc, 0, 0, 0, 0, width, height);
	xcb_flush(connection);
}

// Writes the frame data to just zeroes
// Using memset isn't the most beautiful way to do this, but other methods cause headaches
void Canvas::clear()
{
	int32_t rgb = 0xff000000; // Reset clear color
	xcb_change_gc(connection, gc, XCB_GC_FOREGROUND, &rgb);
	xcb_rectangle_t rect[] = {{0, 0, uint16_t(width), uint16_t(height)}};
	xcb_poly_fill_rectangle(connection, frame, gc, 1, rect);
}

}; // namespace win
