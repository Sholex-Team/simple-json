#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({"r": 22, "rr": 6, "mm": 25, "c": 2})"));
    Json dst(loads(R"({"r": 9, "rz": 6, "b": 22, "c": 2})"));
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
