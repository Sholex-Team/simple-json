#include "types/exceptions/invalid_index.h"

namespace simple_json::types::exceptions {
    const char * InvalidIndex::what() const noexcept {
        switch (used_type) {
            case DataType::integer_type:
                return "Used an index on integer type !";
            case DataType::double_type:
                return "Used an index on double type !";
            case DataType::json_object_type:
                return "Invalid index(integer) used on JsonObject type !";
            case DataType::string_type:
                return "Used an index on string type !";
            case DataType::array_type:
                return "Invalid index(string key) used on Array type !";
            default:
                return "Invalid index used !";
        }
    }

    InvalidIndex::InvalidIndex(const DataType used_type) : JsonException(), used_type (used_type) {}
}
