#include "simple_json.h"
#include <iostream>


using namespace simple_json;
using namespace types;
using namespace indent;

int main() {
    JsonPointer p {"/123/1"};
    std::cout << p;
    return 0;
}
