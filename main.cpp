#include <iostream>
#include <iomanip>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::indent;

int main() {
    JsonObject a {
            {"t5"_json_key, 5}
    };
    a["t10"_json_key] = "ali";
    a["t5"_json_key] = {
            {"a1"_json_key, "sadi"},
            {"a2"_json_key, "sina"},
    };
    a["t9"_json_key] = {"ali", 5};
    std::cout << set_indent(4) << a << std::endl;
    return 0;
}
