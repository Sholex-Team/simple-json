#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a;
    std::cout << a.get("fo", "None") << std::endl;
    return 0;
}
