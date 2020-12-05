
#include "invalid_index_exception.h"

const char *InvalidIndexException::what() const noexcept {
    switch (to) {
        case DataType::integer_type:
            return "invalid used index integer 1";
        case DataType::double_type:
            return "invalid used index double !";
        case DataType::json_type:
            return "invalid used index(\"integer\") in json !";
        case DataType::string_type:
            return "invalid used index(\"string\") in string !";
        case DataType::array_type:
            return "invalid used index(\"string\") in array !";
        default:
            return "Bad indexing !";
    }
}

InvalidIndexException::InvalidIndexException(DataType to) noexcept : JsonException(), to (to) {}