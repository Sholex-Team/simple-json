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
        unknown
    };

    enum StreamType : std::uint8_t {
        indent
    };
}

#endif //SIMPLE_JSON_ENUM_TYPES_H
