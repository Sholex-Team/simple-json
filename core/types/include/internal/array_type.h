#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>

class JsonItem;
typedef std::vector<JsonItem> type_array;
typedef std::initializer_list<JsonItem> array_list_type;

class Array : public type_array {
public:
    // Constructors
    Array() = default;
    Array(Array & array) = default;
    Array(Array && array) noexcept;
    Array(array_list_type & list_initial);
    Array(array_list_type && list_initial);

    // Assignment Operator Overloading
    Array & operator = (const Array & array) = default;
    Array & operator = (Array && array) noexcept = default;

    // Friends
    friend std::ostream & operator << (std::ostream & os, Array && array);
    friend std::ostream & operator << (std::ostream & os, Array & array);
};

#endif //SIMPLE_JSON_ARRAY_TYPE_H
