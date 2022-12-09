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
            case IteratorType::array_iterator_type:
                data = new ArrayIterator {*std::get<IteratorType::array_iterator_type>(data)};
                return;
            case IteratorType::json_object_iterator_type:
                data = new JsonObjectIterator(*std::get<IteratorType::json_object_iterator_type>(data));
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
            case IteratorType::array_iterator_type:
                ++ *std::get<IteratorType::array_iterator_type>(data);
                break;
            case IteratorType::json_object_iterator_type:
                ++ *std::get<IteratorType::json_object_iterator_type>(data);
                break;
            default:
                throw exceptions::InvalidIterator {IteratorType::unknown_iterator};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::decrement_iterator() {
        switch (data.index()) {
            case IteratorType::array_iterator_type:
                -- *std::get<IteratorType::array_iterator_type>(data);
                break;
            case IteratorType::json_object_iterator_type:
                -- *std::get<IteratorType::json_object_iterator_type>(data);
                break;
            default:
                throw exceptions::InvalidIterator {IteratorType::unknown_iterator};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    void JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::clean_memory() noexcept {
        switch (data.index()) {
            case IteratorType::array_iterator_type:
                delete std::get<IteratorType::array_iterator_type>(data);
                return;
            case IteratorType::json_object_iterator_type:
                delete std::get<IteratorType::json_object_iterator_type>(data);
                return;
            default:
                return;
        }
    }

    #pragma endregion

    #pragma region Public Methods

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    template<IteratorType T>
    auto &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::check_type() const {
        if (data.index() != T)
            throw exceptions::InvalidIterator {static_cast<IteratorType>(data.index())};
        return std::get<T>(const_cast<variant_type &>(data));
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    const JsonKey &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::key() const {
        return (*check_type<IteratorType::json_object_iterator_type>())->first;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::value() const {
        return (*check_type<IteratorType::json_object_iterator_type>())->second;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    ReturnType &JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator*() const {
        if (data.index() != IteratorType::array_iterator_type)
            throw exceptions::InvalidDereference {};
        return **std::get<IteratorType::array_iterator_type>(data);
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
            *check_type<IteratorType::array_iterator_type>() + i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator-(long i) const {
        return JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> {
            *check_type<IteratorType::array_iterator_type>() - i};
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator+=(long i) {
         *check_type<IteratorType::array_iterator_type>() += i;
         return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator-=(long i) {
        *check_type<IteratorType::array_iterator_type>() -= i;
        return *this;
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator!=(const JsonIterator<ArrayIterator,
            JsonObjectIterator, ReturnType> &r_iterator) const {
        switch (r_iterator.data.index()) {
            case IteratorType::array_iterator_type:
                return *check_type<IteratorType::array_iterator_type>() != *std::get<IteratorType::array_iterator_type>(
                        r_iterator.data);
            case IteratorType::json_object_iterator_type:
                return *check_type<IteratorType::json_object_iterator_type>() !=
                        *std::get<IteratorType::json_object_iterator_type>(r_iterator.data);
            default:
                throw exceptions::InvalidIterator {IteratorType::unknown_iterator};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    bool JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType>::operator==(const JsonIterator<ArrayIterator,
            JsonObjectIterator, ReturnType> &r_iterator) const {
        switch (r_iterator.data.index()) {
            case IteratorType::array_iterator_type:
                return *check_type<IteratorType::array_iterator_type>() == *std::get<IteratorType::array_iterator_type>(
                        r_iterator.data);
            case IteratorType::json_object_iterator_type:
                return *check_type<IteratorType::json_object_iterator_type>() ==
                        *std::get<IteratorType::json_object_iterator_type>(r_iterator.data);
            default:
                throw exceptions::InvalidIterator {IteratorType::unknown_iterator};
        }
    }

    template<typename ArrayIterator, typename JsonObjectIterator, typename ReturnType>
    JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &JsonIterator<ArrayIterator, JsonObjectIterator,
    ReturnType>::operator=(const JsonIterator<ArrayIterator, JsonObjectIterator, ReturnType> &r_iterator) {
        clean_memory();
        switch (r_iterator.data.index()) {
            case IteratorType::array_iterator_type:
                data = new ArrayIterator {*std::get<IteratorType::array_iterator_type>(r_iterator.data)};
                return *this;
            case IteratorType ::json_object_iterator_type:
                data = new JsonObjectIterator {*std::get<IteratorType::json_object_iterator_type>(r_iterator.data)};
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

    template class JsonIterator<Array::iterator, JsonObject::iterator, Json>;
    template auto &JsonIterator<Array::iterator, JsonObject::iterator, Json>::check_type<types::array_iterator_type>() const;
    template class JsonIterator<Array::const_iterator , JsonObject::const_iterator , const Json>;
    template class JsonIterator<Array::reverse_iterator , JsonObject::reverse_iterator , Json>;
    template class JsonIterator<Array::const_reverse_iterator , JsonObject::const_reverse_iterator , const Json>;

    #pragma endregion
}