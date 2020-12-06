#include <iostream>
#include <iomanip>
#include "simple_json.h"

using namespace simple_json;
using namespace ::types;
using namespace ::indent;

int main() {
    JsonObject a {
            {"t"_json_key, 5}
    };
    std::cout << set_indent() << a << std::endl;
    return 0;
}
