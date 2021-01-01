#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace types;

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
    std::cout << json.at("test/sadi/1"_json_ptr);
    return 0;
}
