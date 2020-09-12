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

void importScene(nlohmann::json sceneJSON)
{
	jdscn::SceneMeta metaTest;

	metaTest = sceneJSON["meta"].get<jdscn::SceneMeta>();

	std::cout << metaTest.version << std::endl;
	std::cout << metaTest.generator << std::endl;
}

} // namespace import
