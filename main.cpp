#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json p(loads(R"({
    "n": "5"
    })"));
    std::cout << set_indent() << p;
    return 0;
}
