#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"([{"reza": 123, "mosi": 321}, {"ali": 456, "sadi": 789}])"));
    Json dst(loads(R"([{"ali": 123, "mosi": 321}, {"hasan": 456, "sadi": 789}])"));
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
