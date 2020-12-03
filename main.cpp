#include <iostream>
#include "types.h"

int main() {
    std::cout << "Start Simple JSON Project!" << std::endl;
    BaseJson *a {new JsonItem<int> {10}};
    std::cout << "Data is " << a -> get_data<int>() << std::endl;
    return 0;
}
