#include <string>

using namespace std;

namespace argparse {

static bool endsWith(const string&, const string&);

class Args {
	public:
	string inputFile;
};

Args parseArgs(int argc, char* argv[]);

}
