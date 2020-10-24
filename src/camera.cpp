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
#include <xcb/xcb_cursor.h>

namespace controls
{

CameraController::CameraController(xcb_connection_t *c)
{
	connection = c;
	keysPressed.fill(false);
	capturingCursor = false;
}

void CameraController::startInputLoop()
{
	std::thread([this]() {
		xcb_generic_event_t *event;
		while ((event = xcb_wait_for_event(connection))) {
			if (event->response_type == XCB_KEY_PRESS || event->response_type == XCB_KEY_RELEASE) {
				// Keyboard press/release
				xcb_key_press_event_t *ev = (xcb_key_press_event_t *)event;
				keysPressed[ev->detail] = event->response_type == XCB_KEY_PRESS;

				// Escape button
				if (event->response_type == XCB_KEY_PRESS && ev->detail == 9) capturingCursor = false;
			} else if (event->response_type == XCB_MOTION_NOTIFY) {
				// Mouse move
				xcb_motion_notify_event_t *ev = (xcb_motion_notify_event_t *)event;
				pointer = jdscn::Position2D({ev->event_x, ev->event_y});

				/* if(capturingCursor) { */
				/* 	xcb_get_pointer_control(connection); */
				/* } */
			} else if (event->response_type == XCB_BUTTON_PRESS) {
				// Mouse button click
				xcb_button_press_event_t *ev = (xcb_button_press_event_t *)event;

				// Left mouse button
				if (ev->detail == 1) capturingCursor = true;
			}
			free(event);
		}
	}).detach();
}

jdscn::Orientation CameraController::cameraRotation(int maxx, int maxy) {
	config::camera_controls camera_controls;
	if(!capturingCursor) return this->originalRotation;
	return jdscn::Orientation({
			this->originalRotation[0] + (float(pointer[1]) - float(maxy) / 2) / camera_controls.sensitivity_y,
			this->originalRotation[1],
			this->originalRotation[2] + (float(pointer[0]) - float(maxx) / 2) / camera_controls.sensitivity_x
			});
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
