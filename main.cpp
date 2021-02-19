#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({
        "n": "rez",
        "a": 12,
        "f": {
                "n": "mosi",
                "a": 5
            }
    })"));
    Json merge_patch(loads(R"({"n": null, "f": {"a": 99, "n": null}})"));
    src.merge_patch(merge_patch);
    std::cout << src << std::endl;
    return 0;
}
