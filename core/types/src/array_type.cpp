#include "array_type.h"
#include "json_item.h"

#pragma region Construcors

Array::Array(Array &&array) noexcept : type_array(std::move(array)) {}

Array::Array(array_list_type & list_initial) : type_array(list_initial) {}

Array::Array(array_list_type && list_initial) : type_array(list_initial) {}

#pragma endregion

#pragma region OS Overloading

std::ostream & operator << (std::ostream & os, Array & array) {
    os << '[';
    for (size_t i {0}; i < array.size(); ++i) {
        os << array.at(i) << ((i == array.size() - 1) ? "" : ", ");
    }
    os << ']';
    return os;
}

std::ostream & operator << (std::ostream &os, Array && array) {
    os << array;
    return os;
}

#pragma endregion
