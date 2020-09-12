#pragma once
#include "scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace fs = std::filesystem;

namespace import
{

std::string readFile(fs::path path);
void importScene(nlohmann::json sceneJSON);

} // namespace import
