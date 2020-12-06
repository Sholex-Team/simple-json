#include <iostream>
#include <iomanip>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace simple_json::indent;

int main() {
    JsonObject a {
            {"t"_json_key, 5}
    };
    std::cout << set_indent(10) << std::setw(10) << a << std::endl;
    return 0;
}
