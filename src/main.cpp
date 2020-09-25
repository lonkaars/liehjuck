#include "argparse.h"
#include "import.h"
#include "scene.h"
#include "win.h"

#include <array>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

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

	const char* windowTitle = "[floating] cool window";
	Win::Canvas canvas(1280, 720, windowTitle);
	jdscn::Color color = {255, 255, 255};

	sleep(2);

	for (int i = 100; i < 1000; i++) {
		canvas.draw(i, 100, color);
	}

	sleep(10);
	return EXIT_SUCCESS;
}
