#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json json (loads(R"({"a": "reza", "b": "sadi", "c": "mosi", "d": [1, 2, 3]})"));
    JsonPatch patch (loads(R"([{ "op": "copy", "from": "/c", "path": "/d/2" }])"));
    patch.apply(json);
    std::cout << json << std::endl;
    return 0;
}
