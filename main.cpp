#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    Json a;
    a["foo"] = "10";
    std::cout << (std::string) a.get("fo", "None");
    return 0;
}
