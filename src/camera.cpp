#include "camera.h"
#include "config.h"
#include "draw.h"
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xcb_event.h>

namespace controls
{

CameraController::CameraController(xcb_connection_t *c)
{
	connection = c;
	keysPressed.fill(false);
	/* XkbSetDetectableAutoRepeat(display, 1, nullptr); */
}

void CameraController::startInputLoop()
{
	std::thread([this]() {
			xcb_generic_event_t *event;
			while ((event = xcb_wait_for_event(connection))) {
				if(event->response_type == XCB_KEY_PRESS || event->response_type == XCB_KEY_RELEASE) {
						xcb_key_press_event_t *ev = (xcb_key_press_event_t *)event;
						keysPressed[ev->detail] = event->response_type == XCB_KEY_PRESS;
				}
				free (event);
			}
		}).detach();
			/* XNextEvent(display, &event); */
			/* if (event.type == KeyPress && keysPressed[event.xkey.keycode] != true) */
			/* 	keysPressed[event.xkey.keycode] = true; */
			/* else if (event.type == KeyRelease) */
			/* 	keysPressed[event.xkey.keycode] = false; */
			/* if(event->response_type == XCB_KEY_PRESS) { */
			/* 	xcb_key_press_event_t *keyboard_event; */
			/* 	keyboard_event = (xcb_key_press_event_t *)keyboard_event; */
			/* 	std::cout << keyboard_event->detail << std::endl; */
			/* } */
			/* std::cout << event->response_type << std::endl; */
			/* free(event); */
			/* } */

			/* xcb_generic_event_t *e; */
			/* while ((e = xcb_wait_for_event (connection))) { */
			/* switch (e->response_type & ~0x80) { */

			/* 	/1* ESC to exit *1/ */
			/* 	case XCB_KEY_PRESS: { */
			/* 		xcb_key_press_event_t *ev; */
			/* 		ev = (xcb_key_press_event_t *)e; */
			/* 		std::cout << ev->detail << std::endl; */
			/* 		if (ev->detail == 9) return; */
			/* 		break; */
			/* 	} */

			/* } */
}

void CameraController::moveCursor()
{
	config::camera_controls camera_controls;
	config::keymap keys;
	float camera_speed = camera_controls.speed / 100;
	this->cursor[0] += camera_speed * float(this->keysPressed[keys.forward]);
	this->cursor[0] -= camera_speed * float(this->keysPressed[keys.backward]);
	this->cursor[1] += camera_speed * float(this->keysPressed[keys.left]);
	this->cursor[1] -= camera_speed * float(this->keysPressed[keys.right]);
	this->cursor[2] += camera_speed * float(this->keysPressed[keys.up]);
	this->cursor[2] -= camera_speed * float(this->keysPressed[keys.down]);
}

} // namespace controls
