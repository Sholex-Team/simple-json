#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace types;
using namespace indent;

int main() {
    Json json {
            {"reza"_json_key, "rrr"},
            {
                "test"_json_key, {
                    {"mosi"_json_key, "mmm"},
                    {"sadi"_json_key, {"sss", "sss 1", "sss 2"}}
                }
            }
    };
    Json & j{json["aaaa"_json_ptr]};
    j = "123";
    std::cout << set_indent() << json;
    return 0;
}
