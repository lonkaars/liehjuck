#include "draw.h"
#include "calc.h"
#include "camera.h"
#include "config.h"
#include "scene.h"
#include "win.h"
#include "debug.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace draw
{

Drawloop::Drawloop(win::Canvas &canvas, jdscn::Scene &scene, float framerate)
	: canvas(canvas), scene(scene)
{
	interval = 1000 / framerate;
	this->canvas = canvas;
	this->scene = scene;
}

void Drawloop::startLoop()
{
	std::thread([this]() {
		int frame = 0;
		config::camera_controls camera_controls;
		config::keymap keymap;
		config::debug_cursor debug_cursor;
		controls::CameraController controller(canvas.connection, &canvas.window);
		controller.startInputLoop();
		controller.cursor = scene.camera.position;
		controller.originalRotation = scene.camera.orientation;
		controller.width = this->canvas.width;
		controller.height = this->canvas.height;
		int maxY = (M_PI - this->scene.camera.orientation[0]) * camera_controls.sensitivity_y;
		int minY = (-this->scene.camera.orientation[0]) * camera_controls.sensitivity_y;
		while (true) {
			if (controller.keysPressed[keymap.exit])
				exit(0);

			std::chrono::time_point nextFrameTime =
				std::chrono::steady_clock::now() + std::chrono::milliseconds(int(interval));

			// Calculate camera movement
			controller.moveCursor(scene.camera.orientation[2]);
			scene.camera.position[0] +=
				(controller.cursor[0] - scene.camera.position[0]) / camera_controls.easing;
			scene.camera.position[1] +=
				(controller.cursor[1] - scene.camera.position[1]) / camera_controls.easing;
			scene.camera.position[2] +=
				(controller.cursor[2] - scene.camera.position[2]) / camera_controls.easing;

			scene.camera.orientation = controller.cameraRotation(maxY, minY);

			scene.draw(canvas, frame);

			if (debug_cursor.on) debug::draw_debug_axes(this->scene.camera, this->canvas);

			std::this_thread::sleep_until(nextFrameTime);
			frame++;
		}
	}).detach();
}

}; // namespace draw
