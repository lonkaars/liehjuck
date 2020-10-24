#include "camera.h"
#include "calc.h"
#include "config.h"
#include "draw.h"
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <xcb/xcb.h>
#include <xcb/xcb_event.h>
#include <xcb/xcb_keysyms.h>

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
			if (event->response_type == XCB_KEY_PRESS || event->response_type == XCB_KEY_RELEASE) {
				xcb_key_press_event_t *ev = (xcb_key_press_event_t *)event;
				keysPressed[ev->detail] = event->response_type == XCB_KEY_PRESS;
			}
			free(event);
		}
	}).detach();
}

void CameraController::moveCursor(float rotation)
{
	config::camera_controls camera_controls;
	config::keymap keys;

	float camera_speed = camera_controls.speed / 100;

	jdscn::FloatXY xmod = calc::rotate2D(jdscn::FloatXY({1, 0}), rotation);
	jdscn::FloatXY ymod = calc::rotate2D(jdscn::FloatXY({0, 1}), rotation);

	this->cursor[0] += camera_speed * float(this->keysPressed[keys.right]) * xmod[0];
	this->cursor[1] += camera_speed * float(this->keysPressed[keys.right]) * xmod[1];
	this->cursor[0] -= camera_speed * float(this->keysPressed[keys.left]) * xmod[0];
	this->cursor[1] -= camera_speed * float(this->keysPressed[keys.left]) * xmod[1];

	this->cursor[0] += camera_speed * float(this->keysPressed[keys.forward]) * ymod[0];
	this->cursor[1] += camera_speed * float(this->keysPressed[keys.forward]) * ymod[1];
	this->cursor[0] -= camera_speed * float(this->keysPressed[keys.backward]) * ymod[0];
	this->cursor[1] -= camera_speed * float(this->keysPressed[keys.backward]) * ymod[1];

	this->cursor[2] += camera_speed * float(this->keysPressed[keys.up]);
	this->cursor[2] -= camera_speed * float(this->keysPressed[keys.down]);
}

} // namespace controls
