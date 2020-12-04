#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a {
            {"name", "reza"},
            {"age", 18},
            {"friends", {"Ali", "Jafar", "Ahmad"}},
            {"enemies", {"Ali", "Jafar", "Ahmad"}},
            {"gates", {"Ali", "Jafar", "Ahmad"}},
    };
    return 0;
}
