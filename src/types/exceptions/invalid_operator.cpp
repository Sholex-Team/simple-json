#include "types/exceptions/invalid_operator.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    InvalidOperator::InvalidOperator(DataType target_type) : base_exceptions::JsonException {},
            used_type {target_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidOperator::what() const noexcept {
        switch (used_type) {
            case DataType::INTEGER_TYPE:
                return "Invalid operator used on integer data type !";
            case DataType::DOUBLE_TYPE:
                return "Invalid operator used on double data type !";
            case DataType::BOOLEAN_TYPE:
                return "Invalid operator used on bool data type !";
            case DataType::NULL_TYPE:
                return "Invalid operator used on null data type !";
            case DataType::STRING_TYPE:
                return "Invalid operator used on std::string data type !";
            case DataType::ARRAY_TYPE:
                return "Invalid operator used on Array data type !";
            case DataType::JSON_OBJECT_TYPE:
                return "Invalid operator used on JsonObject data type !";
            default:
                return "Invalid operator has been used !";
        }
    }

    #pragma endregion
}
