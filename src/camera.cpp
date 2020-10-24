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
