#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    JsonItem item {10};
    int int_item {item};
    std::cout << "Data is " << int_item << std::endl;
    return 0;
}
