#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json p {loads(R"({"value": [2, 1]})")};
    std::cout << set_indent() << p;
    return 0;
}
