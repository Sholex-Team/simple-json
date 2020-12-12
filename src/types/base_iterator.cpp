#include "base_iterator.h"

namespace simple_json::iterators {
    #pragma region Constructors

    JsonIterator::JsonIterator(types::IteratorTypes used_type) : used_type {used_type} {}

    #pragma endregion

    #pragma region Protected Methods

    void JsonIterator::check_json_object() const {
        if (used_type != types::IteratorTypes::json_object_iterator_type) {
            throw exceptions::InvalidType {};
        }
    }

    #pragma endregion
}