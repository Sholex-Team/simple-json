#include "types/exceptions/invalid_index.h"

namespace simple_json::types::exceptions {
    const char * InvalidIndex::what() const noexcept {
        switch (used_type) {
            case DataType::INTEGER_TYPE:
                return "Used an index on integer type !";
            case DataType::DOUBLE_TYPE:
                return "Used an index on double type !";
            case DataType::JSON_OBJECT_TYPE:
                return "Invalid index(integer) used on JsonObject type !";
            case DataType::STRING_TYPE:
                return "Used an index on string type !";
            case DataType::ARRAY_TYPE:
                return "Invalid index(string key) used on Array type !";
            default:
                return "Invalid index used !";
        }
    }

    InvalidIndex::InvalidIndex(const DataType used_type) : JsonException(), used_type (used_type) {}
}
