#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

int main() {
    Json p(loads(R"({"n": "\nhello"})"));
    std::cout << p << '\n' << p.at("n");
    return 0;
}
