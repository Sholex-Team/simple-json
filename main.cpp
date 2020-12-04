#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    JsonItem a {1, 2, 3, 4};
    std::cout << a << std::endl;
    return 0;
}
