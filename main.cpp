#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({"r": {"m": 33}, "c": [2]})"));
    Json dst(loads(R"({"r": {"a": 33, "m": 33}, "c": [1, 2]})"));
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
