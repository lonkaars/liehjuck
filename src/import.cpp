#include "scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace nlohmann
{

template <> struct adl_serializer<jdscn::SceneMeta> {
	static jdscn::SceneMeta from_json(const json &j)
	{
		jdscn::SceneMeta metaOut{j["version"], j["generator"]};
		return metaOut;
	}
};

template <> struct adl_serializer<jdscn::FloatXYZ> {
	static jdscn::FloatXYZ from_json(const json &j)
	{
		jdscn::FloatXYZ out{j["x"], j["y"], j["z"]};
		return out;
	}
};

} // namespace nlohmann

namespace import
{

std::string readFile(std::filesystem::path path)
{
	std::ifstream fileStream(path.string());
	std::string fileString((std::istreambuf_iterator<char>(fileStream)),
						   (std::istreambuf_iterator<char>()));
	return fileString;
}

jdscn::Scene importScene(nlohmann::json sceneJSON)
{
	jdscn::Scene sceneOut;

	sceneOut.meta = sceneJSON["meta"].get<jdscn::SceneMeta>();
	sceneOut.camera.position = sceneJSON["camera"]["position"].get<jdscn::FloatXYZ>();

	return sceneOut;
}

} // namespace import
