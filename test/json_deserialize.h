#include <nlohmann/json.hpp>
#include <string>

using namespace std;
using json = nlohmann::json;

namespace gert {

class testClass {
	public:
	string foo;
	string bar;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(testClass, foo, bar);
};

using gert = testClass;

};

