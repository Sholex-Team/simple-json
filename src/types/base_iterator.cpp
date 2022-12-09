#include "types/base_iterator.h"
#include "types/json.h"

namespace simple_json::iterators {
    #pragma region Constructors

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(const ArrayIterator &array_iterator) :
    data {new ArrayIterator {array_iterator}} {}

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(
            const JsonObjectIterator &json_object_iterator) : data {new JsonObjectIterator {json_object_iterator}} {}

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(
            const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &json_iterator) {
        switch (json_iterator.data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                data = new ArrayIterator {*std::get<IteratorType::ARRAY_ITERATOR_TYPE>(data)};
                return;
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                data = new JsonObjectIterator(*std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(data));
                return;
            default:
                return;
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::JsonIterator(
            JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &&json_iterator) noexcept :
            data {json_iterator.data} {
        json_iterator.data = std::monostate {};
    }

    #pragma endregion

    #pragma region Destructor

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::~JsonIterator() noexcept {
        clean_memory();
    }

    #pragma endregion

    #pragma region Protected Methods

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::increment_iterator() {
        switch (data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                ++ *std::get<IteratorType::ARRAY_ITERATOR_TYPE>(data);
                break;
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                ++ *std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(data);
                break;
            default:
                throw exceptions::InvalidIterator {IteratorType::UNKNOWN_ITERATOR};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::decrement_iterator() {
        switch (data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                -- *std::get<IteratorType::ARRAY_ITERATOR_TYPE>(data);
                break;
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                -- *std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(data);
                break;
            default:
                throw exceptions::InvalidIterator {IteratorType::UNKNOWN_ITERATOR};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::clean_memory() noexcept {
        switch (data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                delete std::get<IteratorType::ARRAY_ITERATOR_TYPE>(data);
                return;
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                delete std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(data);
                return;
            default:
                return;
        }
    }

    #pragma endregion

    #pragma region Public Methods

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    template<IteratorType T>
    auto JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::check_type() const -> decltype(std::get<T>(
            const_cast<variant_type &>(data))) {
        if (data.index() != T)
            throw exceptions::InvalidIterator {static_cast<IteratorType>(data.index())};
        return std::get<T>(const_cast<variant_type &>(data));
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonKey &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::key() const {
        return (*check_type<IteratorType::JSON_OBJECT_ITERATOR_TYPE>())->first;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::value() const {
        return const_cast<ReturnType &>((*check_type<IteratorType::JSON_OBJECT_ITERATOR_TYPE>())->second);
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator*() const {
        if (data.index() != IteratorType::ARRAY_ITERATOR_TYPE)
            throw exceptions::InvalidDereference {};
        return const_cast<ReturnType &>(**std::get<IteratorType::ARRAY_ITERATOR_TYPE>(data));
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType> JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator++(int) {
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {*this};
        increment_iterator();
        return temp;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator,
    JsonObjectIterator, ReturnType>::operator++() {
        increment_iterator();
        return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator--(int) {
        JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> temp {*this};
        decrement_iterator();
        return temp;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator--() {
        decrement_iterator();
        return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator+(long i) const {
        return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {
                *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() + i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator-(long i) const {
        return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {
                *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() - i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator+=(long i) {
         *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() += i;
         return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator-=(long i) {
        *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() -= i;
        return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator!=(const JsonIterator<ArrayIterator,
            JsonObjectIterator, ReturnType> &r_iterator) const {
        switch (r_iterator.data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                return *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() != *std::get<IteratorType::ARRAY_ITERATOR_TYPE>(
                        r_iterator.data);
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                return *check_type<IteratorType::JSON_OBJECT_ITERATOR_TYPE>() !=
                       *std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(r_iterator.data);
            default:
                throw exceptions::InvalidIterator {IteratorType::UNKNOWN_ITERATOR};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator==(const JsonIterator<ArrayIterator,
            JsonObjectIterator, ReturnType> &r_iterator) const {
        switch (r_iterator.data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                return *check_type<IteratorType::ARRAY_ITERATOR_TYPE>() == *std::get<IteratorType::ARRAY_ITERATOR_TYPE>(
                        r_iterator.data);
            case IteratorType::JSON_OBJECT_ITERATOR_TYPE:
                return *check_type<IteratorType::JSON_OBJECT_ITERATOR_TYPE>() ==
                       *std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(r_iterator.data);
            default:
                throw exceptions::InvalidIterator {IteratorType::UNKNOWN_ITERATOR};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator=(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &r_iterator) {
        clean_memory();
        switch (r_iterator.data.index()) {
            case IteratorType::ARRAY_ITERATOR_TYPE:
                data = new ArrayIterator {*std::get<IteratorType::ARRAY_ITERATOR_TYPE>(r_iterator.data)};
                return *this;
            case IteratorType ::JSON_OBJECT_ITERATOR_TYPE:
                data = new JsonObjectIterator {*std::get<IteratorType::JSON_OBJECT_ITERATOR_TYPE>(r_iterator.data)};
                return *this;
            default:
                data = std::monostate {};
        }
        return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator=(JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &&r_iterator) noexcept {
        clean_memory();
        data = r_iterator.data;
        r_iterator.data = std::monostate {};
        return *this;
    }


    // Explicit Template Instantiations
    template class JsonIterator<Array::iterator, JsonObject::iterator, Json>;
    template auto Json::iterator::check_type<IteratorType::UNKNOWN_ITERATOR>() const -> std::monostate &;
    template auto Json::iterator::check_type<IteratorType::ARRAY_ITERATOR_TYPE>() const -> Array::iterator *&;
    template auto Json::iterator::check_type<
            IteratorType::JSON_OBJECT_ITERATOR_TYPE>() const -> JsonObject::iterator *&;

    template class JsonIterator<Array::const_iterator, JsonObject::const_iterator, const Json>;
    template auto Json::const_iterator::check_type<IteratorType::UNKNOWN_ITERATOR>() const -> std::monostate &;
    template auto Json::const_iterator::check_type<
            IteratorType::ARRAY_ITERATOR_TYPE>() const -> Array::const_iterator *&;
    template auto Json::const_iterator::check_type<
            IteratorType::JSON_OBJECT_ITERATOR_TYPE>() const -> JsonObject::const_iterator *&;

    template class JsonIterator<Array::reverse_iterator, JsonObject::reverse_iterator, Json>;
    template auto Json::reverse_iterator::check_type<IteratorType::UNKNOWN_ITERATOR>() const -> std::monostate &;
    template auto Json::reverse_iterator::check_type<
            IteratorType::ARRAY_ITERATOR_TYPE>() const -> Array::reverse_iterator *&;
    template auto Json::reverse_iterator::check_type<
            IteratorType::JSON_OBJECT_ITERATOR_TYPE>() const -> JsonObject::reverse_iterator *&;

    template class JsonIterator<Array::const_reverse_iterator, JsonObject::const_reverse_iterator, const Json>;
    template auto Json::const_reverse_iterator::check_type<IteratorType::UNKNOWN_ITERATOR>() const -> std::monostate &;
    template auto Json::const_reverse_iterator::check_type<
            IteratorType::ARRAY_ITERATOR_TYPE>() const -> Array::const_reverse_iterator *&;
    template auto Json::const_reverse_iterator::check_type<
            IteratorType::JSON_OBJECT_ITERATOR_TYPE>() const -> JsonObject::const_reverse_iterator *&;

    #pragma endregion
}