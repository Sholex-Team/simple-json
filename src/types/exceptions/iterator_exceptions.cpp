#include "types/exceptions/iterator_exceptions.h"

namespace simple_json::iterators::exceptions {
    #pragma region Constructors

    InvalidIteration::InvalidIteration() : from {types::DataType::unknown} {}

    InvalidIteration::InvalidIteration(types::DataType from_type) : from {from_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidDereference::what() const noexcept {
        return "Invalid Dereference operator on type JsonObject";
    }

    const char * InvalidIteration::what() const noexcept {
        switch (from) {
            case types::DataType::integer_type:
                return "Invalid Iteration on integer type";
            case types::DataType::double_type:
                return "Invalid Iteration on double type";
            case types::DataType::string_type:
                return "Invalid Iteration on std::string type";
            default:
                return "Invalid Iteration on non-JsonObject/Array type";
        }
    }

    const char * InvalidType::what() const noexcept {
        return "Invalid call of key-value methods on non-JsonObject type !";
    }

    #pragma endregion
}