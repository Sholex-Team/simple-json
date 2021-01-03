#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace types;
using namespace indent;

int main() {
    JsonPointer p {"/123/1"};
    double test {Json(10.5)};
    std::cout << test;
    return 0;
}
