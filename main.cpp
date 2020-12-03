#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a;
    a["foo"] = {10};
    Json b {a};
    return 0;
}
