#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({"n": "1", "a": "2"})"));
    std::string s {dumps(src, 2)};
    std::cout << s;
    return 0;
}
