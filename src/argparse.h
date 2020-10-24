#pragma once
#include <string>

/** @file argparse.h */

/** @brief Command line argument parsing */
namespace argparse
{

/**
 * @brief C++20 replacement for std::string::ends_with
 *
 * Because Ubuntu's package repositories still provide gcc 9.2, we have to use c++17
 *
 * @param input
 * @param suffix String to check the input string against
 *
 * @return bool true if str ends with suffix
 */
static bool endsWith(const std::string &input, const std::string &suffix);

/** @brief Return type of the parseArgs function */
class Args
{
	public:
	std::string inputFile;
};

/**
 * @brief Parse argc and argv into the Args class
 *
 * @param argc
 * @param argv[]
 *
 * @return Args
 */
Args parseArgs(int argc, char *argv[]);

} // namespace argparse
