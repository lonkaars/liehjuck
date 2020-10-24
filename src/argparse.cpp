#include "argparse.h"
#include <argagg/argagg.hpp>
#include <iostream>

namespace argparse
{

static bool endsWith(const std::string &input, const std::string &suffix)
{
	return input.size() >= suffix.size() &&
		   0 == input.compare(input.size() - suffix.size(), suffix.size(), suffix);
}

Args parseArgs(int argc, char *argv[])
{
	Args out;
	argagg::parser argparser{{{"help", {"-h", "--help"}, "shows this help message", 0}}};

	std::ostringstream usage;
	usage << "Usage: " << argv[0] << " [options, -h|--help] input" << std::endl << std::endl;

	std::ostringstream controls;
	controls << "Controls: (these can be edited through config.h)" << std::endl
			 << std::endl
			 << "Basic movement: " << std::endl
			 << "wasd    -> forward, backward, left, right" << std::endl
			 << "<ctrl>  -> down" << std::endl
			 << "<space> -> up" << std::endl
			 << std::endl
			 << "Camera movement: " << std::endl
			 << "<left mouse button> -> enter focus" << std::endl
			 << "<esc>               -> exit focus" << std::endl
			 << "While in focus, moving the mouse will move the camera" << std::endl
			 << std::endl
			 << "Miscellaneous:" << std::endl
			 << "q -> exit" << std::endl
			 << std::endl;

	argagg::parser_results args;
	try {
		args = argparser.parse(argc, argv);
	} catch (const std::exception &e) {
		std::cerr << usage.str() << argparser << std::endl
				  << "Encountered exception while parsing arguments: " << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	if (args["help"]) {
		argagg::fmt_ostream fmt(std::cerr);
		std::cerr << usage.str() << argparser << std::endl << std::endl << controls.str();
		exit(EXIT_SUCCESS);
	}

	// no file specified
	if (args.pos.size() == 0) {
		std::cout << usage.str();
		exit(EXIT_FAILURE);
	}

	// check for .jdscn file extension
	out.inputFile = args.pos[0];
	if (!endsWith(out.inputFile, ".jdscn")) {
		std::cout << "The file you specified doesn't have the jdscn file extension!" << std::endl;
		std::cout << usage.str();
		exit(EXIT_FAILURE);
	}

	return out;
}

} // namespace argparse
