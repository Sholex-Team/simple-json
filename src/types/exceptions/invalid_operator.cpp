#include "types/exceptions/invalid_operator.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    InvalidOperator::InvalidOperator(int target_type) : base_exceptions::JsonException {}, used_type {target_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidOperator::what() const noexcept {
        switch (used_type) {
            case DataType::integer_type:
                return "Invalid operator used on integer data type !";
            case DataType::double_type:
                return "Invalid operator used on double data type !";
            case DataType::boolean_type:
                return "Invalid operator used on bool data type !";
            case DataType::null_type:
                return "Invalid operator used on null data type !";
            case DataType::string_type:
                return "Invalid operator used on std::string data type !";
            case DataType::array_type:
                return "Invalid operator used on Array data type !";
            case DataType::json_object_type:
                return "Invalid operator used on JsonObject data type !";
            default:
                return "Invalid operator has been used !";
        }
    }

    #pragma endregion
}
