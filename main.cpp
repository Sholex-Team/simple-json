#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a {
            {"hi, {1, 2, 3}},
            {"test", "test_2"}
    };
    return 0;
}
