#include "array_type.h"

#pragma region Construcors

Array::Array() : type_array() {}

Array::Array(Array &&array) noexcept : type_array(std::move(array)) {}

#pragma endregion

std::ostream &operator<<(std::ostream &os, Array & array) {
    os << "[";
    for (int i {0}; i < array.size(); ++i) {
        os << array.at(i) << ((i == array.size() - 1) ? "" : ", ");
    }
    os << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, Array && array) {
    os << array;
    return os;
}
