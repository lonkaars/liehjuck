#include "import.h"
#include "scene.h"
#include <argagg/argagg.hpp>
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using namespace std;

// std::string::ends_with replacement for c++ 17 because ubuntu 20.04 poopy
static bool endsWith(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		   0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

int main(int argc, char *argv[])
{
	argagg::parser argparser{{{"help", {"-h", "--help"}, "shows this help message", 0}}};

	ostringstream usage;
	usage << "Usage: " << argv[0] << " [options] input" << endl << endl;

	argagg::parser_results args;
	try {
		args = argparser.parse(argc, argv);
	} catch (const exception &e) {
		argagg::fmt_ostream fmt(cerr);
		fmt << usage.str() << argparser << endl
			<< "Encountered exception while parsing arguments: " << e.what() << endl;
		return EXIT_FAILURE;
	}

	if (args["help"]) {
		argagg::fmt_ostream fmt(cerr);
		fmt << usage.str() << argparser;
		return EXIT_SUCCESS;
	}

	if (args.pos.size() == 0) {
		cout << usage.str();
		return EXIT_FAILURE;
	}

	string input_file = args.pos[0];
	if (!endsWith(input_file, ".jdscn")) {
		cout << "The file you specified doesn't have the jdscn file extension!" << endl;
		cout << usage.str();
		return EXIT_FAILURE;
	}

	string scene_file = import::readFile(input_file);
	nlohmann::json scene_json = nlohmann::json::parse(scene_file);
	jdscn::Scene scene_jdscn = import::importScene(scene_json);

	cout << "jdscn version: " << scene_jdscn.meta.version << endl
		 << "generator: " << scene_jdscn.meta.generator << endl
		 << "camera name: " << scene_jdscn.camera.meta.name << endl;
	for (jdscn::Light light : scene_jdscn.lights)
		cout << "light: " << light.meta.name << endl;
	for (jdscn::Object object : scene_jdscn.objects)
		cout << "object: " << object.meta.name << ", tris: " << object.vertices.size() << endl;

	return EXIT_SUCCESS;
}
