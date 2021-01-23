#include "types/base_iterator.h"

namespace simple_json::iterators {
    #pragma region Constructors

    JsonIterator::JsonIterator(const types::IteratorTypes used_type) : used_type {used_type} {}

    #pragma endregion

    #pragma region Protected Methods

    void JsonIterator::check_json_object() const {
        if (used_type != types::IteratorTypes::json_object_iterator_type) {
            throw exceptions::InvalidType {};
        }
    }

    void JsonIterator::check_array_type() const {
        if (used_type != types::IteratorTypes::array_iterator_type) {
            throw simple_json::types::exceptions::InvalidOperator {};
        }
    }

    #pragma endregion

    #pragma region Public Methods

    void JsonIterator::check_type(types::IteratorTypes target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidIterator {target_type};
        }
    }

    #pragma endregion
}