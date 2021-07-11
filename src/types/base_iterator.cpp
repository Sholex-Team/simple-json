#include "types/base_iterator.h"

namespace simple_json::iterators {
    #pragma region Constructors

    BaseJsonIterator::BaseJsonIterator(const IteratorTypes used_type) : used_type {used_type} {}

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(const ArrayIterator & array_iterator) :
    BaseJsonIterator {IteratorTypes::array_iterator_type}, array_iterator {new ArrayIterator {array_iterator}} {}

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<
            ArrayIterator, JsonObjectIterator, ReturnType
            >::JsonIterator(const JsonObjectIterator & json_object_iterator) :
    BaseJsonIterator {used_type},
    json_object_iterator {new JsonObjectIterator {json_object_iterator}} {}

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

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(
            const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & json_iterator
            ) : BaseJsonIterator {json_iterator.used_type} {
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = new ArrayIterator {* json_iterator.array_iterator};
            return;
        }
        json_object_iterator = new JsonObjectIterator {* json_iterator.json_object_iterator};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> && json_iterator
            ) noexcept : BaseJsonIterator {json_iterator.used_type} {
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = new ArrayIterator {* json_iterator.array_iterator};
            json_iterator.array_iterator = nullptr;
            return;
        }
        json_object_iterator = new JsonObjectIterator {* json_iterator.json_object_iterator};
        json_iterator.json_object_iterator = nullptr;
    }

    #pragma endregion

    #pragma region Public Methods

    void BaseJsonIterator::check_type(IteratorTypes target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidIterator {target_type};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonKey & JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::key() const {
        check_json_object();
        return (* json_object_iterator)->first;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType & JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::value() const {
        check_json_object();
        return (* json_object_iterator)->second;
    }

    #pragma endregion

    #pragma region Private Methods

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::increment_iterator() {
        if (used_type == IteratorTypes::array_iterator_type)
            ++ * array_iterator;
        else
            ++ * json_object_iterator;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::decrement_iterator() {
        if (used_type == IteratorTypes::array_iterator_type)
            -- * array_iterator;
        else
            -- * json_object_iterator;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::clean_memory() {
        if (used_type == IteratorTypes::array_iterator_type)
            delete array_iterator;
        else
            delete json_object_iterator;
    }

    #pragma endregion

    #pragma Operator Overloading
    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType & JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator*() const {
        if (used_type != IteratorTypes::array_iterator_type) {
            throw iterators::exceptions::InvalidDereference {};
        }
        return * * array_iterator;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<
    ArrayIterator, JsonObjectIterator, ReturnType>::operator++(int) {
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {* this};
        increment_iterator();
        return temp;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator++() {
        increment_iterator();
        return * this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<
    ArrayIterator, JsonObjectIterator, ReturnType>::operator--(int) {
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {* this};
        decrement_iterator();
        return temp;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator--() {
        decrement_iterator();
        return * this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<
    ArrayIterator, JsonObjectIterator, ReturnType>::operator+(long i) const {
        check_array_type();
        return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {* array_iterator + i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<
    ArrayIterator, JsonObjectIterator, ReturnType>::operator-(long i) const {
        check_array_type();
        return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {* array_iterator - i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & JsonIterator<
            ArrayIterator, JsonObjectIterator, ReturnType>::operator+=(long i) {
        check_array_type();
        * array_iterator += i;
        return * this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & JsonIterator<
            ArrayIterator, JsonObjectIterator, ReturnType>::operator-=(long i) {
        check_array_type();
        * array_iterator -= i;
        return * this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator!=(
            const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return * array_iterator != * r_iterator.array_iterator;
        }
        return * json_object_iterator != * r_iterator.json_object_iterator;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator==(
            const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return * array_iterator == * r_iterator.array_iterator;
        }
        return * json_object_iterator == * r_iterator.json_object_iterator;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator=(
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> && r_iterator) noexcept {
        clean_memory();
        used_type = r_iterator.used_type;
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = r_iterator.array_iterator;
            r_iterator.array_iterator = nullptr;
        } else {
            json_object_iterator = r_iterator.json_object_iterator;
            r_iterator.json_object_iterator = nullptr;
        }
        return * this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator=(
            const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> & r_iterator) {
        clean_memory();
        used_type = r_iterator.used_type;
        if (used_type == IteratorTypes::array_iterator_type)
            array_iterator = new ArrayIterator {* r_iterator.array_iterator};
        else
            json_object_iterator = new JsonObjectIterator {* r_iterator.json_object_iterator};
        return * this;
    }

    #pragma endregion

    #pragma region Destructor

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::~JsonIterator() noexcept {
        clean_memory();
    }

    #pragma endregion
}