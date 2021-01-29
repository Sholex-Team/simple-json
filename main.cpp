#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json src(loads(R"({
                     "v":10})"));
    dump(src, "/home/rez/Desktop/test_2.json");
    return 0;
}
