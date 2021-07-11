#include "types/base_iterator.h"

namespace simple_json::iterators {
    #pragma region Constructors

    BaseJsonIterator::BaseJsonIterator(const IteratorTypes used_type) : used_type {used_type} {}

    #pragma endregion

    #pragma region Protected Methods

    void BaseJsonIterator::check_json_object() const {
        if (used_type != IteratorTypes::json_object_iterator_type) {
            throw exceptions::InvalidType {};
        }
    }

    void BaseJsonIterator::check_array_type() const {
        if (used_type != IteratorTypes::array_iterator_type) {
            throw types::exceptions::InvalidOperator {};
        }
    }

    #pragma endregion

    #pragma region Public Methods

    void BaseJsonIterator::check_type(IteratorTypes target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidIterator {target_type};
        }
    }

    #pragma endregion
}