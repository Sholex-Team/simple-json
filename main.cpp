#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a {
            {"a", Json {
                    {"a", 8}
            }}
    };
    return 0;
}
