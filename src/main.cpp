#include "import.h"
#include "scene.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;

int main()
{
	std::string default_scene_file = import::readFile("./test/default_scene.jdscn");
	nlohmann::json default_scene_json = nlohmann::json::parse(default_scene_file);
	jdscn::Scene default_scene_jdscn = import::importScene(default_scene_json);

	std::cout << "jdscn version: " << default_scene_jdscn.meta.version << std::endl;
	std::cout << "generator: " << default_scene_jdscn.meta.generator << std::endl;
	std::cout << "camera name: " << default_scene_jdscn.camera.meta.name << std::endl;
	for (jdscn::Light light : default_scene_jdscn.lights)
		std::cout << "light: " << light.meta.name << std::endl;
	for (jdscn::Object object : default_scene_jdscn.objects)
		std::cout << "object: " << object.meta.name << ", tris: " << object.vertices.size() << std::endl;

	return 0;
}
