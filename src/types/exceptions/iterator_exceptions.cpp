#include "types/exceptions/iterator_exceptions.h"

namespace simple_json::iterators::exceptions {
    #pragma region Constructors

    InvalidIteration::InvalidIteration(const types::DataType used_type) : used_type {used_type} {}

    InvalidIterator::InvalidIterator(types::IteratorType used_type) : used_type {used_type} {}

    #pragma endregion

    #pragma region Public Methods

    const char * InvalidDereference::what() const noexcept {
        return "Invalid Dereference operator on type JsonObject";
    }

    const char * InvalidIteration::what() const noexcept {
        switch (used_type) {
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

    const char * InvalidIterator::what() const noexcept {
        switch (used_type) {
            case types::IteratorType::ARRAY_ITERATOR_TYPE:
                return "Can not perform this operation on an Array iterator!";
            case types::IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                return "Can not perform this operation on a JsonObject iterator!";
            default:
                return "Can not perform this operation on an Unknown Type iterator!";
        }
    }

    #pragma endregion
}
