#include "argparse.h"
#include "draw.h"
#include "import.h"
#include "scene.h"
#include "win.h"

#include <array>
#include <iostream>
#include <math.h>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>

using namespace std;

int main(int argc, char *argv[])
{
	argparse::Args arguments = argparse::parseArgs(argc, argv);

	string scene_file = import::readFile(arguments.inputFile);
	nlohmann::json scene_json = nlohmann::json::parse(scene_file);
	jdscn::Scene scene_jdscn = import::importScene(scene_json);

	cout << "jdscn version: " << scene_jdscn.meta.version << endl
		 << "generator: " << scene_jdscn.meta.generator << endl
		 << "camera name: " << scene_jdscn.camera.meta.name << endl;
	for (jdscn::Light light : scene_jdscn.lights)
		cout << "light: " << light.meta.name << endl;
	for (jdscn::Object object : scene_jdscn.objects)
		cout << "object: " << object.meta.name << ", tris: " << object.vertices.size() << endl;

	const char *windowTitle = "[floating] cool window";
	Win::Canvas canvas(1280, 720, windowTitle);
	/* draw::Drawloop drawloop(canvas, scene_jdscn, 30.0f); */
	/* drawloop.startLoop(); */

	// https://stackoverflow.com/questions/2100654/ignore-auto-repeat-in-x11-applications
	array<bool, 255> keysPressed;
	fill(keysPressed.begin(), keysPressed.end(), false);
	XEvent e;
	XSelectInput(canvas.display, canvas.window, KeyPressMask | KeyReleaseMask);
	XkbSetDetectableAutoRepeat(canvas.display, 1, nullptr);
	for(;;) {
		int p = XNextEvent(canvas.display, &e);

		if(e.type == KeyPress && keysPressed[e.xkey.keycode] != true) {
			std::cout << e.xkey.keycode << " " << "on t+" << e.xkey.time << std::endl;
			keysPressed[e.xkey.keycode] = true;
		} else if (e.type == KeyRelease) {
			std::cout << e.xkey.keycode << " " << "off t+" << e.xkey.time << std::endl;
			keysPressed[e.xkey.keycode] = false;
		}

	}

	this_thread::sleep_for(60s);

	return EXIT_SUCCESS;
}
