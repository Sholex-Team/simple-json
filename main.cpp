#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    JsonItem test {Array {1, 2, 3}};
    Json a {
            {"name", "reza"},
            {"age", 18},
            {"friends", {"Ali"}},
    };
    return 0;
}
