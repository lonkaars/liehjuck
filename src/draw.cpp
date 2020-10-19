#include "draw.h"
#include "scene.h"
#include "win.h"

#include <iostream>
#include <chrono>
#include <thread>

namespace draw
{

Drawloop::Drawloop(Win::Canvas& c, jdscn::Scene& s, float framerate)
{
	interval = 1000/framerate;
	canvas = c;
	scene = s;
}

void Drawloop::startLoop()
{
	std::thread([this]()
	{
		int frame = 0;
		while(true)
		{
			std::chrono::time_point nextFrameTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(int(interval));
			scene.draw(canvas, frame);
			std::this_thread::sleep_until(nextFrameTime);
			frame++;
		}
	}).detach();
}

}; // draw
