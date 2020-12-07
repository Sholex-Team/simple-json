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
    a["test"_json_key] = {1, 2, 3, {4, 5}};
    a["test"_json_key][3][3] = {"hi"_json_key, 5};
    std::cout << set_indent(4) << a << std::endl;
    return 0;
}
