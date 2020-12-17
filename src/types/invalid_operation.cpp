#include "invalid_operation.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    InvalidOperation::InvalidOperation(DataType used_type) : used_type {used_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidOperation::what() const noexcept {
        switch (used_type) {
            case DataType::json_object_type:
                return "Invalid JsonObject operation on object !";
            case DataType::array_type:
                return "Invalid Array operation on object !";
            default:
                return "Invalid operation on object !";
        }
    }

#pragma endregion
}