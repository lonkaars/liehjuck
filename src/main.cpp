#include "argparse.h"
#include "config.h"
#include "draw.h"
#include "import.h"
#include "scene.h"
#include "win.h"

#include <xcb/xcb.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>
#include <signal.h>
#include <execinfo.h>
#include <unistd.h>

using namespace std;

void errorHandler(int signal) {
	void *array[10];
	size_t size;
	size = backtrace(array, 10);
	std::cout << "Error: code " << signal << std::endl;
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char *argv[])
{
	// Error handling first
	signal(SIGSEGV, errorHandler);

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

	config::renderSettings render;
	win::Canvas canvas(render.width, render.height, render.title);

	draw::Drawloop drawloop(canvas, scene_jdscn, render.framerate);
	drawloop.startLoop();

	this_thread::sleep_for(60s);

	return EXIT_SUCCESS;
}
