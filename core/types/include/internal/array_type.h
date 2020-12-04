#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>

class JsonItem;

typedef std::vector<JsonItem> type_array;

class Array : public type_array {
public:
    // Constructors
    Array() = default;
    Array(Array & array) = default;
    Array(Array && array) noexcept;
    Array(std::initializer_list<JsonItem> list_initial);

    // Assignment Operator Overloading
    Array & operator = (const Array & json_item);
    Array & operator = (Array && json_item) noexcept;

    // Friends
    friend std::ostream & operator << (std::ostream & os, Array && array);
    friend std::ostream & operator << (std::ostream & os, Array & array);
};

#endif //SIMPLE_JSON_ARRAY_TYPE_H
