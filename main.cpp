#include "simple_json.h"
#include <iostream>

using namespace simple_json;
using namespace deserializer;
using namespace serializer;
using namespace types;
using namespace indent;

int main() {
    Json src(load("/home/antiwanted/Desktop/test.json"));
    dump(src, "/home/antiwanted/Desktop/test_2.json");
    return 0;
}
