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
    using array_list_type = std::initializer_list<Json>;

    class Array : public type_array {
    private:
        std::ostream & stream_without_indent(std::ostream & os) const;
        std::ostream & stream_with_indent(std::ostream & os, size_t indent_size) const;
    public:
        // Constructors
        Array() = default;
        Array(const Array & array) = default;
        Array(Array && array) noexcept = default;
        Array(const array_list_type & list_initial);

        // Assignment Operator Overloading
        Array & operator=(const Array & array) = default;
        Array & operator=(Array && array) noexcept = default;

        // Friends
        friend std::ostream & operator<<(std::ostream & os, const Array & array);
        friend JsonObject;
    };

    std::ostream & operator<<(std::ostream & os, const Array & array);
}

#endif //SIMPLE_JSON_ARRAY_TYPE_H
