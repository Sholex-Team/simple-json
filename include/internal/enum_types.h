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
        json_type,
        null_type,
        unknown
    };
}

#endif //SIMPLE_JSON_ENUM_TYPES_H
