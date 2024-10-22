#include "../src/import.h"
#include "../src/jdscn_types.h"
#include "../src/scene.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

namespace
{

std::string defaultSceneContent;
nlohmann::json defaultSceneJSON;

TEST(ImportTest, ReadFile)
{
	std::string defaultScenePath = "./experiments/render-tests/default_scene.jdscn";
	defaultSceneContent = import::readFile(defaultScenePath);
}

TEST(ImportTest, StringToJSON) { defaultSceneJSON = nlohmann::json::parse(defaultSceneContent); }

TEST(ImportTest, ImportScene) { jdscn::Scene defaultScene = import::importScene(defaultSceneJSON); }

} // namespace
