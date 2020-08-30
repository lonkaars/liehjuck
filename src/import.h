#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "scene.h"

namespace fs = std::filesystem;

namespace import {
	std::string readFile(fs::path path);
	jdscn::scene importScene(nlohmann::json sceneJSON);
}
