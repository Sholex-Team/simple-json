#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json json (loads(R"({"a": "reza", "b": [1, 2, 3, 4, 5, 6], "c": "mosi", "d": [1, 2, 3, 4, 5, 6]})"));
    JsonPatch patch (loads(R"([{ "op": "movee", "from": "/b/2", "path": "/d/4" }])"));
    patch.apply(json);
    std::cout << json << std::endl;
    return 0;
}
