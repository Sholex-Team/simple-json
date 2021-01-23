#include "simple_json.h"
#include <iostream>
#include <string>


using namespace simple_json;
using namespace deserializer;
using namespace types;
using namespace indent;

void test_func(std::string my_func(char ch)) {
    std::cout << my_func('h') << std::endl;
}

int main() {
    test_func([] (char ch) {return std::string {"hello there"} + ch;});
    return 0;
}
