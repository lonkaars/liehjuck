#pragma once
#include "scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

/** @file import.h */

namespace fs = std::filesystem;

/** @brief namespace handling filesystem reads, and deserialization */
namespace import
{

/**
 * @brief Read the contents of a file to a std::string
 * @param fs::path path of the file to read
 * @return std::string file contents
 */
std::string readFile(fs::path);

/**
 * @brief Deserialize nlohmann::json to jdscn::Scene
 * @param nlohmann::json input json
 * @return jdscn::Scene
 */
jdscn::Scene importScene(nlohmann::json);

} // namespace import
