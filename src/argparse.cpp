#include "argparse.h"
#include <argagg/argagg.hpp>
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace argparse
{
// std::string::ends_with replacement for c++ 17 because ubuntu 20.04 poopy
static bool endsWith(const std::string &str, const std::string &suffix)
{
	return str.size() >= suffix.size() &&
		   0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

Args parseArgs(int argc, char *argv[])
{
	Args out;
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
		exit(EXIT_FAILURE);
	}

	if (args["help"]) {
		argagg::fmt_ostream fmt(cerr);
		fmt << usage.str() << argparser;
		exit(EXIT_SUCCESS);
	}

	// no file specified
	if (args.pos.size() == 0) {
		cout << usage.str();
		exit(EXIT_FAILURE);
	}

	// check for .jdscn file extension
	out.inputFile = args.pos[0];
	if (!endsWith(out.inputFile, ".jdscn")) {
		cout << "The file you specified doesn't have the jdscn file extension!" << endl;
		cout << usage.str();
		exit(EXIT_FAILURE);
	}

	return out;
}

} // namespace argparse
