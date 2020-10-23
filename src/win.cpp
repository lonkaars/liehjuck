#include "win.h"
#include "scene.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sys/utsname.h>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/xcb_pixel.h>
#include <xcb/xcb_image.h>

namespace win
{

Canvas::Canvas(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	uint32_t mask;
	uint32_t values[2];

	connection = xcb_connect(NULL, NULL);
	display = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = display->black_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS;

	window_id = xcb_generate_id(connection);
	window = xcb_create_window(connection,
							   XCB_COPY_FROM_PARENT, window_id, display->root,
							   0, 0, width, height,
							   0,
							   XCB_WINDOW_CLASS_INPUT_OUTPUT,
							   display->root_visual,
							   mask, values);
  
	xcb_map_window(connection, window_id);

	xcb_change_property (connection, XCB_PROP_MODE_REPLACE, window_id,
						 XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 8,
						 strlen(title), title);

	gc_id = xcb_generate_id(connection);
	gc = xcb_create_gc(connection,
					   gc_id, window_id,
					   mask, values);

	frame_id = xcb_generate_id(connection);
	frame = xcb_create_pixmap(connection, 24, frame_id, window_id, width, height);

	xcb_flush(connection);

	/* xcb_generic_event_t *event; */
	/* while ((event = xcb_wait_for_event(connection))) { */
	/* 	if (event->response_type == XCB_EXPOSE) { */
	/* 		xcb_copy_area(connection, frame_id, window_id, gc_id, 0, 0, 0, 0, width, height); */
	/* 		xcb_flush(connection); */
	/* 	} */

	/* 	if (event->response_type == XCB_KEY_PRESS) { */
	/* 		exit(0); */
	/* 	} */
	/* } */
}

// Draws a pixel at given x and y coordinates in the color that is specified in c
void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 + x;
	y = this->height / 2 - y;

	if(x > this->width ||
	   x < 0 ||
	   y > this->height ||
	   y < 0) return;

	int color = c[2] + c[1] * 256 + c[0] * 256 * 256;
	xcb_point_t point[] = {{10, 10}};
	xcb_poly_point(connection, XCB_COORD_MODE_ORIGIN, frame_id, gc_id, 1, point);
}

// Sends the stored frame to the x server
void Canvas::flush()
{
	xcb_copy_area(connection, frame_id, window_id, gc_id, 0, 0, 0, 0, width, height);
	xcb_flush(connection);
}

// Writes the frame data to just zeroes
// Using memset isn't the most beautiful way to do this, but other methods cause headaches
void Canvas::clear()
{
	/* const size_t data_size = frame->bytes_per_line * frame->height; */
	/* memset(frame->data, 0, data_size); */	
}

}; // namespace win
