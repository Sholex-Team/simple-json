#include "iterator_exceptions.h"

namespace simple_json::iterators::exceptions {
    const char * InvalidDereference::what() const noexcept {
        return "Invalid Dereference operator on type JsonObject";
    }

    InvalidIteration::InvalidIteration() : from {types::DataType::unknown} {}

    InvalidIteration::InvalidIteration(types::DataType from_type) : from {from_type} {}

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
}