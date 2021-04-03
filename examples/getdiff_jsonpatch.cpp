#include <iostream>
#include <simple_json.h>

using namespace simple_json::types;
using namespace simple_json::deserializer;

int main() {
    Json json1 (loads(R"({"foo": "bar"})"));
    Json json2 (loads(R"({"number": 1})"));
    JsonPatch patch {json1.get_diff(json2)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
