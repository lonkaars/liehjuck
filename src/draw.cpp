#include "draw.h"
#include "scene.h"
#include "win.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace draw
{

Drawloop::Drawloop(Win::Canvas& canvas, jdscn::Scene& scene, float framerate) : canvas(canvas), scene(scene)
{
	interval = 1000 / framerate;
	this->canvas = canvas;
	this->scene = scene;
}

void Drawloop::startLoop()
{
	std::thread([this]() {
		int frame = 0;
		while (true) {
			std::chrono::time_point nextFrameTime =
				std::chrono::steady_clock::now() + std::chrono::milliseconds(int(interval));
			scene.draw(canvas, frame);
			std::this_thread::sleep_until(nextFrameTime);
			frame++;
		}
	}).detach();
}

}; // namespace draw
