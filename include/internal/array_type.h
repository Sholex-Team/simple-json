#ifndef SIMPLE_JSON_ARRAY_TYPE_H
#define SIMPLE_JSON_ARRAY_TYPE_H

#include <vector>
#include <ostream>
#include "indent.h"
#include <iomanip>

namespace simple_json::types {
    class Json;
    class JsonObject;
    using type_array = std::vector<Json>;
    using array_list_type = std::initializer_list<std::initializer_list<Json>>;

    class Array : public type_array {
    private:
        std::ostream & stream_without_indent(std::ostream &) const;
        std::ostream & stream_with_indent(std::ostream &, size_t) const;
    public:
        // Constructors
        Array() = default;
        Array(Array &) = default;
        Array(Array &&) noexcept = default;
        Array(const array_list_type &);

        // Assignment Operator Overloading
        Array & operator=(const Array &) = default;
        Array & operator=(Array &&) noexcept = default;

        // Friends
        friend std::ostream & operator<<(std::ostream &, const Array &);
        friend JsonObject;
    };

    std::ostream & operator<<(std::ostream &, const Array &);
}

#endif //SIMPLE_JSON_ARRAY_TYPE_H
