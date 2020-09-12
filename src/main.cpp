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
}
