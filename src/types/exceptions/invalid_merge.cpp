#include "types/exceptions/invalid_merge.h"

namespace simple_json::types::exceptions {
    InvalidMerge::InvalidMerge(DataType target_type) : target_type {target_type} {}

    const char * InvalidMerge::what() const noexcept {
        switch (target_type) {
            case DataType::array_type:
                return "Can not merge a JSON Object with an Array !";
            case DataType::json_object_type:
                return "Can not merge an Array with a JSON Object !";
            default:
                return "Invalid merge operation !";
        }
    }
}
