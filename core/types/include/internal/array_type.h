#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>

//class JsonItem;

typedef std::vector<int> type_array;

class Array : public type_array {
public:

    // Constructors
    Array();
    Array(Array & array) = default;
    Array(Array && array) noexcept;

    // Friends
    friend std::ostream & operator << (std::ostream & os, Array && array);
    friend std::ostream & operator << (std::ostream & os, Array & array);
};

#endif //SIMPLE_JSON_ARRAY_TYPE_H
