#include "camera.h"
#include "config.h"
#include "draw.h"
#include <array>
#include <chrono>
#include <iostream>
#include <thread>

namespace controls
{

CameraController::CameraController(Display *d, Window *w)
{
	display = d;
	window = *w;
	keysPressed.fill(false);
	XSelectInput(display, window, KeyPressMask | KeyReleaseMask);
	XkbSetDetectableAutoRepeat(display, 1, nullptr);
}

void CameraController::startInputLoop()
{
	std::thread([this]() {
		for (;;) {
			XEvent event;
			XNextEvent(display, &event);
			if (event.type == KeyPress && keysPressed[event.xkey.keycode] != true)
				keysPressed[event.xkey.keycode] = true;
			else if (event.type == KeyRelease)
				keysPressed[event.xkey.keycode] = false;
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
