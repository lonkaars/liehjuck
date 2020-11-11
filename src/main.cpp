#include "argparse.h"
#include "config.h"
#include "draw.h"
#include "import.h"
#include "scene.h"
#include "win.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#ifdef UNIT_TEST_BINARY

#include <iostream>
#include <gtest/gtest.h>

GTEST_API_ int main(int argc, char **argv) {
	std::cout << "Running main() from " << __FILE__ << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#else

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

	config::renderSettings render;
	win::Canvas canvas(render.width, render.height, render.title);
	canvas.clear();

	draw::Drawloop drawloop(canvas, scene_jdscn, render.framerate);
	drawloop.startLoop();

	while (1) {
	};

	return EXIT_SUCCESS;
}

#endif
