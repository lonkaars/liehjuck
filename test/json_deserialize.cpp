#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include "json_deserialize.h"

using namespace std;
using json = nlohmann::json;

int main() {
	string jsonString = "{\"foo\":\"nyek\", \"bar\": \"haggiepang\"}";

	json jsonAsJson = json::parse(jsonString);

	gert::testClass gert = jsonAsJson.get<gert::testClass>();
	
	return 0;
}

