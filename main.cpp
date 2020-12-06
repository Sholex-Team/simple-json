#include <iostream>
#include "simple_json.h"

using namespace simple_json::types;

int main() {
    JsonObject a {
            {"t"_json_key, 5}
    };
    std::cout << unset_indent << a;
    return 0;
}
