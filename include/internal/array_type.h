#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>

namespace simple_json::types {
    class Json;
    typedef std::vector<Json> type_array;
    typedef std::initializer_list<Json> array_list_type;

    class Array : public type_array {
    public:
        // Constructors
        Array() = default;
        Array(Array &) = default;
        Array(Array &&) noexcept = default;
        Array(array_list_type &);
        Array(array_list_type &&);

        // Assignment Operator Overloading
        Array & operator=(const Array &) = default;
        Array & operator=(Array &&) noexcept = default;

        // Friends
        friend std::ostream & operator<<(std::ostream &, Array &&);
        friend std::ostream & operator<<(std::ostream &, Array &);
    };

    std::ostream & operator<<(std::ostream &, Array &);
    std::ostream & operator<<(std::ostream &, Array &&);
}

#endif //SIMPLE_JSON_ARRAY_TYPE_H
