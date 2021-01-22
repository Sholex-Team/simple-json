#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"([1, 2, 3])"));
    Json dst(loads(R"([1, 3, 2])"));
    JsonPatch patch {src.get_diff(dst)};
    return 0;
}
