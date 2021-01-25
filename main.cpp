#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({"r": {"m": 33}, "c": [2, 1]})"));
    Json dst(loads(R"({"r": {"a": 33, "m": 33}, "c": [1, 2]})"));
    JsonPatch patch {src.get_diff(dst)};
    patch.apply(src);
    std::cout << src << std::endl;
    return 0;
}
