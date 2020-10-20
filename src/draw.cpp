#include "draw.h"
#include "scene.h"
#include "win.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace draw
{

/**
 * @brief Drawloop class
 *
 * @param c Canvas to draw on
 * @param s Scene to render
 * @param framerate Number of frames to render per second
 */
Drawloop::Drawloop(Win::Canvas &c, jdscn::Scene &s, float framerate)
{
	interval = 1000 / framerate;
	canvas = c;
	scene = s;
}

/**
 * @brief Start the draw loop
 *
 * Opens a new thread and runs code to draw the scene
 */
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
