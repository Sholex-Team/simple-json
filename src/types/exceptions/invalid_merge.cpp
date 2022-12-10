#include "types/exceptions/invalid_merge.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    InvalidMerge::InvalidMerge(DataType target_type) : target_type {target_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidMerge::what() const noexcept {
        switch (target_type) {
            case DataType::ARRAY_TYPE:
                return "Can not merge a JSON Object with an Array !";
            case DataType::JSON_OBJECT_TYPE:
                return "Can not merge an Array with a JSON Object !";
            default:
                return "Invalid merge operation !";
        }
    }

    #pragma endregion
}
