#include "camera.h"
#include "calc.h"
#include "config.h"
#include "draw.h"
#include <array>
#include <math.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <xcb/xcb.h>
#include <xcb/xfixes.h>
#include <xcb/xtest.h>

namespace controls
{

CameraController::CameraController(xcb_connection_t *c, xcb_window_t *w)
{
	connection = c;
	window = *w;
	keysPressed.fill(false);
	capturingCursor = false;
}

void CameraController::startInputLoop()
{
	std::thread([this]() {
		xcb_generic_event_t *event;
		bool fake_next = false;
		pointer = jdscn::Position2D({0, 0});
		xcb_xfixes_query_version(connection, 4, 0);
		while ((event = xcb_wait_for_event(connection))) {
			if (event->response_type == XCB_KEY_PRESS || event->response_type == XCB_KEY_RELEASE) {
				// Keyboard press/release
				xcb_key_press_event_t *ev = (xcb_key_press_event_t *)event;
				keysPressed[ev->detail] = event->response_type == XCB_KEY_PRESS;

				// Escape button
				if (event->response_type == XCB_KEY_PRESS && ev->detail == 9) {
					capturingCursor = false;
					xcb_xfixes_show_cursor(connection, window);
				}
			} else if (event->response_type == XCB_MOTION_NOTIFY) {
				// Mouse move
				xcb_motion_notify_event_t *ev = (xcb_motion_notify_event_t *)event;
				if (capturingCursor) {
					// warp cursor to window center
					pointer[0] += width / 2 - ev->event_x;
					pointer[1] += height / 2 - ev->event_y;
					if (!fake_next) {
						xcb_test_fake_input(connection, XCB_MOTION_NOTIFY, 1, 0,
											xcb_window_t{XCB_NONE}, width / 2 - ev->event_x,
											height / 2 - ev->event_y, 0);
						xcb_flush(connection);
						fake_next = true;
					} else {
						fake_next = false;
					}
				}
			} else if (event->response_type == XCB_BUTTON_PRESS) {
				// Mouse button click
				xcb_button_press_event_t *ev = (xcb_button_press_event_t *)event;

				// Left mouse button
				if (ev->detail == 1) {
					capturingCursor = true;
					xcb_xfixes_hide_cursor(connection, window);
				}
			}
			free(event);
		}
	}).detach();
}

jdscn::Orientation CameraController::cameraRotation(int maxY, int minY)
{
	config::camera_controls camera_controls;
	if (!capturingCursor)
		return this->originalRotation;

	pointer[1] = pointer[1] > maxY ? maxY : pointer[1] < minY ? minY : pointer[1];

	return jdscn::Orientation(
		{this->originalRotation[0] + float(pointer[1]) / camera_controls.sensitivity_y,
		 this->originalRotation[1],
		 this->originalRotation[2] + float(pointer[0]) / camera_controls.sensitivity_x});
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
