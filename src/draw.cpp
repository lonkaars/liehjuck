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
#include <math.h>

namespace draw
{

Drawloop::Drawloop(win::Canvas &canvas, jdscn::Scene scene,  jdscn::Scene startscene, float framerate)
	: canvas(canvas), scene(scene)
{
	interval = 1000 / framerate;
	this->canvas = canvas;
	this->scene = scene;
	this->startScene = startscene;
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
		int currentScene = 0;
		int state = 0;
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
		
			// Animation instructions
			if(scene.meta.generator == "presentation")
			{
				
				if(frame < 300)
				{
					if(currentScene == 0)
					{
						scene = startScene;
						scene.objects.erase(scene.objects.begin()+1, scene.objects.end());	
						currentScene++;
					}
					scene.objects[0].position[0] = startScene.objects[0].position[0] + 3.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = startScene.objects[0].position[1] + 3.0f * sin(float(frame)/20.0f);
					
				}
				else if(frame < 600)
				{
					if(currentScene == 1)
					{
						scene = startScene;
						scene.objects.erase(scene.objects.begin()+2, scene.objects.end());
						scene.objects.push_back(startScene.objects[1]);
						scene.objects[2].material.color = {0, 200, 0};
						scene.objects[2].position = {-2.5, 0, 0};
						currentScene++;
					}

					scene.objects[0].scale[0] = 0.5;
					scene.objects[0].scale[1] = 0.5;
					scene.objects[0].scale[2] = 0.5;
					scene.objects[0].orientation[2] += 0.2;
					
					scene.objects[0].position[0] = startScene.objects[0].position[0] + 6.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = startScene.objects[0].position[1] + 3.0f * sin(float(frame)/10.0f);
				}
				/*else if(frame < 900)
				{
					
					if(currentScene == 2)
					{
						scene = startScene;
						scene.objects.erase(scene.objects.begin()+1, scene.objects.end());
						scene.objects.push_back(startScene.objects[0]);
						scene.objects.push_back(startScene.objects[0]);
						scene.objects.push_back(startScene.objects[0]);

						scene.objects[0].material.color = {255, 0, 0};
						
						scene.objects[1].material.color = {0, 255, 0};
						
						scene.objects[2].material.color = {0, 0, 255};
						
						scene.objects[3].material.color = {255, 255, 255};

						currentScene++;
					}
					
					scene.objects[0].position[0] = scene.camera.position[0] + 3.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = scene.camera.position[1] + 3.0f * sin(float(frame)/20.0f);

					scene.objects[0].position[0] = scene.camera.position[0] + 3.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = scene.camera.position[1] + 3.0f * sin(float(frame)/20.0f);

					scene.objects[0].position[0] = scene.camera.position[0] + 3.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = scene.camera.position[1] + 3.0f * sin(float(frame)/20.0f);

					scene.objects[0].position[0] = scene.camera.position[0] + 3.0f * cos(float(frame)/20.0f);
					scene.objects[0].position[1] = scene.camera.position[1] + 3.0f * sin(float(frame)/20.0f);
				}*/
				else if(frame < 900)
				{
					
					if(currentScene == 2)
					{
						scene = startScene;
						scene.objects.erase(scene.objects.begin()+2, scene.objects.end());
						scene.objects.push_back(startScene.objects[1]);
						scene.objects[0].material.color = {248, 24, 148};	
						scene.objects[2].material.color = {0, 200, 0};
						scene.objects[2].position = {-4, 0, 0};
						
						scene.objects[1].position = {4, 0, 0};
						
						currentScene++;
					}
					
					scene.objects[0].position[0] += 2.0 * sin(float(frame)/20.0f);

					scene.objects[1].orientation[1] += 0.2;
					scene.objects[2].orientation[1] += 0.2;

				}
			}

			scene.draw(canvas, frame);

			if (debug_cursor.on) debug::draw_debug_axes(this->scene.camera, this->canvas);

			std::this_thread::sleep_until(nextFrameTime);
			frame++;
		}
	}).detach();
}

}; // namespace draw
