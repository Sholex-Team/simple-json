#include <iostream>
#include <simple_json.h>

using namespace simple_json::types;
using namespace simple_json::deserializer;

int main() {
    Json json (loads(R"({"foo": "bar"})"));
    JsonPatch patch (loads(R"(
            [
                {"op": "add", "path": "/number", "value": "1"},
                {"op": "move", "from": "/foo", "path": "/bar"}
            ]
    )"));
    patch.apply(json);
    std::cout << json << std::endl;
    return 0;
}
