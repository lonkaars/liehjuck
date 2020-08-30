#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "scene.h"

namespace import {
	std::string readFile(std::filesystem::path path) {
		std::ifstream fileStream(path.string());
		std::string fileString((std::istreambuf_iterator<char>(fileStream)),
				(std::istreambuf_iterator<char>()));
		return fileString;
	}

	jdscn::scene importScene(nlohmann::json sceneJSON) {
		jdscn::scene sceneOut;
		
		return sceneOut;
	}
}

