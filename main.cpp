#include <iostream>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::indent;

int main() {
    Json a {
            {"t5"_json_key, 5},
            {"names"_json_key, {"Ali", "Ahmad", "Reza", {{"test"_json_key, 5}}}},
    };
    std::cout << set_indent(4) << a << std::endl;
    return 0;
}
