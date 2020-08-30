#include "scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace import
{

std::string readFile(std::filesystem::path path)
{
	std::ifstream fileStream(path.string());
	std::string fileString((std::istreambuf_iterator<char>(fileStream)),
						   (std::istreambuf_iterator<char>()));
	return fileString;
}

jdscn::scene importScene(nlohmann::json sceneJSON)
{
	jdscn::scene sceneOut;

	return sceneOut;
}

} // namespace import
