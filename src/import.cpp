#include "scene.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace import
{

std::string readFile(std::string path)
{
	std::ifstream fileStream(path);
	std::string fileString((std::istreambuf_iterator<char>(fileStream)),
						   (std::istreambuf_iterator<char>()));
	return fileString;
}

jdscn::Scene importScene(nlohmann::json sceneJSON) { return sceneJSON.get<jdscn::Scene>(); }

} // namespace import
