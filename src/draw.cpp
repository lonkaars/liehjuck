#include "draw.h"
#include "calc.h"
#include "camera.h"
#include "scene.h"
#include "win.h"

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
		/* controls::CameraController controller(canvas.display, &canvas.window); */
		/* controller.startInputLoop(); */
		/* controller.cursor = scene.camera.position; */
		while (true) {
			std::chrono::time_point nextFrameTime =
				std::chrono::steady_clock::now() + std::chrono::milliseconds(int(interval));

			// Calculate camera movement
			/* controller.moveCursor(); */
			/* jdscn::Position relativeCursor = */
			/* 	calc::rotate3D(controller.cursor, jdscn::Orientation({0, 0, 0})); */
			/* // FIXME: interpolating as in test/camera-controls/sketch.js */
			/* scene.camera.position = relativeCursor; */

			scene.draw(canvas, frame);

			std::this_thread::sleep_until(nextFrameTime);
			frame++;
		}
	}).detach();
}

}; // namespace draw
