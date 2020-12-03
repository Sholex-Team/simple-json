#ifndef SIMPLE_JSON_ENUM_TYPES_H
#define SIMPLE_JSON_ENUM_TYPES_H
#include <cinttypes>
#include <string>
enum DataType : std::uint8_t {
    integer_type,
    string_type,
    double_type,
    array_type,
    json_type,
    unknown
};

std::string type_convertor(DataType type);
#endif //SIMPLE_JSON_ENUM_TYPES_H
