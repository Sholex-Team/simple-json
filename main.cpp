#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src (loads(R"({"a": "reza", "b": [1, 2, 3, 4, 5, 6], "c": "mosi", "d": [1, 2, 3, 4, 5, 6]})"));
    JsonPatch patch {loads(R"([{ "op": "add", "value": "test", "path": "/d~0" }])")};
    std::cout << patch.get_json() << std::endl;
    patch.apply(src);
    std::cout << src << std::endl;
    return 0;
}
