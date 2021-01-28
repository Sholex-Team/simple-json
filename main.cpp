#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src (loads(R"({"a": "reza", "b": [1, 2, 3, 4, 5, 6], "c": "mosi", "d": [1, 2, 3, 4, 5, 6]})"));
    Json dst (loads(R"({"a": "ali", "b": [4, 2, 1], "c": "mosi", "z": [1, 2, 3, 4, 5, 6]})"));
    JsonPatch patch{dst.get_diff(src)};
    std::cout << patch.get_json() << std::endl;
    patch.apply(dst);
    std::cout << dst << std::endl;
    return 0;
}
