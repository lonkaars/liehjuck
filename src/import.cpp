#include "scene.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace nlohmann
{

template <> struct adl_serializer<jdscn::sceneMeta> {
	static jdscn::sceneMeta from_json(const json &j)
	{
		jdscn::sceneMeta metaOut{j["version"], j["generator"]};
		return metaOut;
	}
};

template <> struct adl_serializer<jdscn::floatXYZ> {
	static jdscn::floatXYZ from_json(const json &j)
	{
		jdscn::floatXYZ out{j["x"], j["y"], j["z"]};
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

jdscn::scene importScene(nlohmann::json sceneJSON)
{
	jdscn::scene sceneOut;

	sceneOut.meta = sceneJSON["meta"].get<jdscn::sceneMeta>();
	sceneOut.camera.position = sceneJSON["camera"]["position"].get<jdscn::floatXYZ>();

	return sceneOut;
}

} // namespace import
