#include "types/exceptions/wrong_type.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    WrongType::WrongType(DataType used_type) : base_exceptions::JsonException {}, used_type {used_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * WrongType::what() const noexcept {
        switch (used_type) {
            case DataType::integer_type:
                return "Attempt to access wrong data on int typed data !";
            case DataType::double_type:
                return "Attempt to access wrong data on double typed data !";
            case DataType::boolean_type:
                return "Attempt to access wrong data on bool typed data !";
            case DataType::null_type:
                return "Attempt to access wrong data on null typed data !";
            case DataType::string_type:
                return "Attempt to access wrong data on std::string typed data !";
            case DataType::array_type:
                return "Attempt to access wrong data on Array typed data !";
            case DataType::json_object_type:
                return "Attempt to access wrong data on JsonObject typed data type !";
            default:
                return "Attempt to access data with wrong type !";
        }
    }

    #pragma endregion
}
