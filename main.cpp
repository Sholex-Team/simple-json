#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace types;
using namespace indent;

void test(double test_arg) {
    std::cout << test_arg << std::endl;
}

int main() {
    JsonPointer p {"/123/1"};
    return 0;
}
