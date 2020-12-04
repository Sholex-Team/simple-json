#include "array_type.h"
#include "json_item.h"

#pragma region Construcors

Array::Array(Array &&array) noexcept : type_array(std::move(array)) {}

#pragma endregion

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

Array::Array(std::initializer_list<JsonItem> list_initial) : type_array(list_initial){}

#pragma region Assignment Operator Overloading

Array &Array::operator=(const Array &json_item) {
    type_array::operator=(json_item);
    return *this;
}

Array &Array::operator=(Array &&json_item) noexcept {
    type_array::operator=(json_item);
    return *this;
}

#pragma endregion