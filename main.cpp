#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"([1, 2])"));
    Json dst(loads(R"([2, 1])"));
    JsonPatch patch {src.get_diff(dst)};
    std::cout << patch.get_json() << std::endl;
    return 0;
}
