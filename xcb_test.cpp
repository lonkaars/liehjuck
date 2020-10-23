#include <stdio.h>
#include <stdlib.h>

#include <xcb/xcb.h>

int main()
{
	xcb_point_t points[] = {{10, 10}, {10, 20}, {20, 10}, {20, 20}};
	xcb_connection_t *connection = xcb_connect(NULL, NULL);
	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;
	xcb_drawable_t window = screen->root;
	uint32_t    rgb = 0xFFFF00FF;
	uint32_t    mask = XCB_GC_FOREGROUND;
	xcb_gcontext_t gc;
	gc = xcb_generate_id(connection);
	uint32_t values[2] = {screen->white_pixel, 0};
	xcb_create_gc(connection, gc, window, XCB_GC_FOREGROUND, &rgb);
	window = xcb_generate_id(connection);
	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = screen->black_pixel;
	values[1] = XCB_EVENT_MASK_EXPOSURE;
	xcb_create_window(connection,
					  XCB_COPY_FROM_PARENT,
					  window,
					  screen->root,
					  0, 0,
					  150, 150,
					  0,
					  XCB_WINDOW_CLASS_INPUT_OUTPUT,
					  screen->root_visual,
					  mask, values);
	xcb_map_window(connection, window);
	xcb_flush(connection);
	xcb_generic_event_t *event;
	while ((event = xcb_wait_for_event(connection))) {
		switch (event->response_type & ~0x80) {
		case XCB_EXPOSE:
			xcb_poly_point(connection, XCB_COORD_MODE_ORIGIN, window, gc, 4, points);
			xcb_flush(connection);
			break;
		default:
			break;
		}
		free(event);
	}
	return 0;
}
