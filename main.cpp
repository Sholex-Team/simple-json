#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({"c": 3})"));
    Json dst(loads(R"({"r": 3, "a": 3})"));
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
