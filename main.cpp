#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a;
    auto result = a.get("fo", "None");
    std::cout << result << std::endl;
    return 0;
}
