#include "draw.h"
#include "scene.h"
#include "win.h"

#include <iostream>
#include <chrono>
#include <thread>

namespace draw
{

Drawloop::Drawloop(Win::Canvas& canvas, jdscn::Scene scene, float framerate)
{
	interval = 1000/framerate;
	c = canvas;
	s = scene;
}

void Drawloop::startLoop()
{
	std::thread([interval = interval, &c = c]()
	{
		jdscn::Color col = {255, 255, 255};
		int pixelspot = 0;
		while(true)
		{
			std::chrono::time_point nextFrameTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(int(interval));
			c.draw(pixelspot, pixelspot, col);
			std::this_thread::sleep_until(nextFrameTime);
			pixelspot++;
		}
	}).detach();
}

}; // draw
