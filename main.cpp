#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json p(loads(R"({
        "121": null,
        "22325": true,
        "3": [true, 1111, "12345", null],
        "3561984152": [true, 1111, "12345", null, false]
})"));
    std::cout << set_indent() << p;
    return 0;
}
