#include "camera.h"
#include "draw.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <array>

namespace controls {

CameraController::CameraController(Display *d, Window *w) {
	display = d;
	window = *w;
	/* std::fill_n(keysPressed, 255, false); */
	keysPressed.fill(false);
	XSelectInput(display, window, KeyPressMask | KeyReleaseMask);
	XkbSetDetectableAutoRepeat(display, 1, nullptr);
}

void CameraController::startInputLoop() {
	std::thread([this](){
		for(;;) {
			XEvent event;
			XNextEvent(display, &event);
			if(event.type == KeyPress && keysPressed[event.xkey.keycode] != true)
				keysPressed[event.xkey.keycode] = true;
			else if (event.type == KeyRelease)
				keysPressed[event.xkey.keycode] = false;
		}
	}).detach();
}

}
