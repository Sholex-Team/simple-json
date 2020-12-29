#ifndef SIMPLE_JSON_ENUM_TYPES_H
#define SIMPLE_JSON_ENUM_TYPES_H

#include <cinttypes>
#include <string>

namespace simple_json::types {
    enum DataType : std::uint8_t {
        integer_type,
        string_type,
        double_type,
        boolean_type,
        array_type,
        json_object_type,
        null_type,
        string_key_type,
        unknown
    };

    enum IteratorTypes : std::uint8_t  {
        array_iterator_type,
        json_object_iterator_type
    };
}

#endif //SIMPLE_JSON_ENUM_TYPES_H
