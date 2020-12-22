#include "json.h"
#include "array_type.h"
#include "enum_types.h"
#include "bad_conversion.h"
#include "stream_exceptions.h"
#include "invalid_index.h"
#include "iterator_exceptions.h"
#include <utility>
#include <invalid_operator.h>

namespace simple_json::types {
    #pragma region Constructors
    Json::Json(double data) : data_double {data}, used_type {DataType::double_type} {}

    Json::Json(long int data) : data_int {data}, used_type {DataType::integer_type} {}

    Json::Json(int data) : data_int {data}, used_type {DataType::integer_type} {}

    Json::Json(bool data) : data_boolean {data}, used_type {DataType::boolean_type} {}

    Json::Json(std::nullptr_t t) : used_type(DataType::null_type) {}

    Json::Json(Array data) : data_array {new Array(std::move(data))},
    used_type {DataType::array_type} {}

    Json::Json(Array && data) : data_array {new Array(std::move(data))},
    used_type {DataType::array_type} {}

    Json::Json(array_list_type & list_initial) : data_array {new Array{list_initial}},
    used_type(DataType::array_type) {}

    Json::Json(array_list_type && list_initial) : data_array {new Array{list_initial}},
    used_type(DataType::array_type) {}

    Json::Json(std::string data) : data_string {new std::string {std::move(data)}},
    used_type {DataType::string_type} {}

    Json::Json(std::string && data) : data_string {new std::string {std::move(data)}},
    used_type {DataType::string_type} {}

    Json::Json(const char * data) : data_string {new std::string {data}}, used_type {DataType::string_type} {}

    Json::Json(JsonObject data) : data_json_object {new JsonObject {std::move(data)}},
    used_type {DataType::json_object_type} {}

    Json::Json(JsonObject && data) : data_json_object {new JsonObject {std::move(data)}},
    used_type {DataType::json_object_type} {}

    Json::Json(json_list_type & initializer_list) : data_json_object {new JsonObject {initializer_list}},
                                                    used_type {DataType::json_object_type} {}

    Json::Json(json_list_type && initializer_list) : data_json_object {new JsonObject {initializer_list}},
                                                     used_type {DataType::json_object_type} {}

    Json::Json(const Json & json_item) : used_type {json_item.used_type} {
        copy(json_item);
    }

    Json::Json(Json && json_item) noexcept : used_type {json_item.used_type} {
        move(json_item);
    }

    Json::Json() : used_type {DataType::json_object_type}, data_json_object {new JsonObject {}} {}

    Json::Json(const DataType object_type) :
    used_type {object_type} {
        create_object();
    }

    #pragma endregion

    #pragma region Operator Overloading

    Json & Json::operator=(array_list_type & array_list) {
        used_type = DataType::array_type;
        data_array = new Array(array_list);
        return * this;
    }

    Json & Json::operator=(json_list_type & json_list) {
        used_type = DataType::json_object_type;
        data_json_object = new JsonObject(json_list);
        return * this;
    }

    Json & Json::operator=(DataType object_type) {
        used_type = object_type;
        create_object();
        return * this;
    }

    Json::operator int() const {
        if (used_type == DataType::integer_type) {
            return data_int;
        }
        throw exceptions::BadConversion {DataType::integer_type};
    }

    Json::operator double() const {
        if (used_type == DataType::double_type) {
            return data_double;
        }
        throw exceptions::BadConversion {DataType::double_type};
    }

    Json::operator std::string() const {
        if (used_type == DataType::string_type) {
            return * data_string;
        }
        throw exceptions::BadConversion {DataType::string_type};
    }

    Json::operator Array() const {
        if (used_type == DataType::array_type) {
            return * data_array;
        }
        throw exceptions::BadConversion {DataType::array_type};
    }

    Json::operator JsonObject() const {
        if (used_type == DataType::json_object_type) {
            return * data_json_object;
        }
        throw exceptions::BadConversion {DataType::json_object_type};
    }

    Json & Json::operator=(const Json & json_item) {
        used_type = json_item.used_type;
        copy(json_item);
        return * this;
    }

    Json & Json::operator=(Json && json_item) noexcept {
        used_type = json_item.used_type;
        move(json_item);
        return * this;
    }

    Json & Json::operator[](const int & index) {
        if (used_type == DataType::array_type) {
            return data_array->at(index);
        }
        throw exceptions::InvalidIndexException {used_type};
    }

    Json & Json::operator[](const char * & index) {
        if (used_type == DataType::json_object_type) {
            return data_json_object->at(JsonKey {index});
        }
        throw exceptions::InvalidIndexException {used_type};
    }

    bool Json::operator==(const Json & json_item) const {
        if (json_item.used_type != used_type) {
            return false;
        }
        switch (used_type) {
            case DataType::integer_type:
                return data_int == json_item.data_int;
            case DataType::string_type:
                return data_string == json_item.data_string;
            case DataType::double_type:
                return data_double == json_item.data_double;
            case DataType::boolean_type:
                return data_boolean == json_item.data_boolean;
            case DataType::array_type:
                return data_array == json_item.data_array;
            case DataType::json_object_type:
                return data_json_object == json_item.data_json_object;
            default:
                return true;
        }
    }

    bool Json::operator==(const Json && json_item) const {
        return * this == json_item;
    }

    #pragma endregion

    #pragma region Destructor
    Json::~Json() {
        switch (used_type) {
            case DataType::array_type:
                delete data_array;
                return;
            case DataType::json_object_type:
                delete data_json_object;
                return;
            case DataType::string_type:
                delete data_string;
                return;
            default:
                return;
        }
    }

    #pragma endregion Destructor

    #pragma region Private Methods
    void Json::move(Json & json_item) noexcept {
        switch (json_item.used_type) {
            case DataType::integer_type:
                data_int = json_item.data_int;
                return;
            case DataType::double_type:
                data_double = json_item.data_double;
                return;
            case DataType::boolean_type:
                data_boolean = json_item.data_boolean;
                return;
            case DataType::string_type:
                data_string = json_item.data_string;
                json_item.data_string = nullptr;
                return;
            case DataType::array_type:
                data_array = json_item.data_array;
                json_item.data_array = nullptr;
                return;
            case DataType::json_object_type:
                data_json_object = json_item.data_json_object;
                json_item.data_json_object = nullptr;
                return;
            default:
                return;
        }
    }

    void Json::copy(const Json & json_item) {
        switch (json_item.used_type) {
            case DataType::integer_type:
                data_int = json_item.data_int;
                return;
            case DataType::double_type:
                data_double = json_item.data_double;
                return;
            case DataType::boolean_type:
                data_boolean = json_item.data_boolean;
                return;
            case DataType::string_type:
                data_string = new std::string {*json_item.data_string};
                return;
            case DataType::array_type:
                data_array = new Array {*json_item.data_array};
                return;
            case DataType::json_object_type:
                data_json_object = new JsonObject {*json_item.data_json_object};
                return;
            default:
                return;
        }
    }

    void Json::create_object() {
        switch (used_type) {
            case DataType::integer_type:
                data_int = 0;
                return;
            case DataType::double_type:
                data_double = 0.0;
                return;
            case DataType::string_type:
                data_string = new std::string {};
                return;
            case DataType::array_type:
                data_array = new Array {};
                return;
            case DataType::json_object_type:
                data_json_object = new JsonObject {};
                return;
            case DataType::boolean_type:
                data_boolean = false;
                return;
            default:
                return;
        }
    }

    void Json::check_type(DataType target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidOperation {target_type};
        }
    }

    #pragma endregion

    #pragma region OS Overloading
    std::ostream & operator<<(std::ostream & os, const Json & json_item) {
        switch (json_item.used_type) {
            case DataType::integer_type:
                os << json_item.data_int;
                break;
            case DataType::string_type:
                os << '"' << * (json_item.data_string) << '"';
                break;
            case DataType::double_type:
                os << json_item.data_double;
                break;
            case DataType::boolean_type:
                os << json_item.data_boolean;
                break;
            case DataType::array_type:
                os << * json_item.data_array;
                break;
            case DataType::json_object_type:
                os << * json_item.data_json_object;
                break;
            case DataType::null_type:
                os << nullptr;
                break;
            default:
                throw serializer::exceptions::StreamInsertionException();
        }
        return os;
    }

    #pragma endregion

    #pragma region Public Methods

    Json & Json::at(const int index) {
        return operator[](index);
    }

    Json & Json::at(const char * index) {
        return operator[](index);
    }

    void Json::push_back(const Json & new_item) {
        check_type(DataType::array_type);
        data_array->push_back(new_item);
    }

    void Json::insert(const pair_type & new_item) {
        check_type(DataType::json_object_type);
        data_json_object->insert(new_item);
    }

    void Json::push_back(Json && new_item) {
        check_type(DataType::array_type);
        data_array->push_back(std::move(new_item));
    }

    void Json::insert(pair_type && new_item) {
        check_type(DataType::json_object_type);
        data_json_object->insert(std::move(new_item));
    }

    Json & Json::back() const noexcept {
        check_type(DataType::array_type);
        return data_array->back();
    }

    #pragma endregion

    #pragma region Iterators

    // Constructors
    Json::iterator::iterator(iterator && r_iterator) noexcept : iterators::JsonIterator {r_iterator.used_type} {
        if (used_type == IteratorTypes::json_object_iterator_type) {
            json_object_iterator = r_iterator.json_object_iterator;
            r_iterator.json_object_iterator = nullptr;
        } else {
            array_iterator = r_iterator.array_iterator;
            r_iterator.array_iterator = nullptr;
            r_iterator.array_iterator = nullptr;
        }
    }

    Json::iterator::iterator(const iterator & r_iterator) : iterators::JsonIterator {r_iterator.used_type} {
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = new Array::iterator {* r_iterator.array_iterator};
        } else {
            json_object_iterator = new JsonObject::iterator {* r_iterator.json_object_iterator};
        }
    }

    Json::iterator::iterator(const Array::iterator & array_iterator) :
    iterators::JsonIterator {IteratorTypes::array_iterator_type},
    array_iterator {new Array::iterator {array_iterator}} {}


    Json::iterator::iterator(const JsonObject::iterator & json_object_iterator) :
    iterators::JsonIterator {IteratorTypes::json_object_iterator_type},
    json_object_iterator {new JsonObject::iterator {json_object_iterator}} {}

    Json::const_iterator::const_iterator(const Array::const_iterator & array_iterator) :
    iterators::JsonIterator {IteratorTypes::array_iterator_type},
    array_iterator {new Array::const_iterator {array_iterator}} {}

    Json::const_iterator::const_iterator(const JsonObject::const_iterator & json_object_iterator) :
    iterators::JsonIterator {IteratorTypes::json_object_iterator_type},
    json_object_iterator {new JsonObject::const_iterator {json_object_iterator}} {}

    Json::const_iterator::const_iterator(const Json::const_iterator & r_iterator) :
    iterators::JsonIterator {r_iterator.used_type} {
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = new Array::const_iterator {* r_iterator.array_iterator};
        } else {
            json_object_iterator = new JsonObject::const_iterator {* r_iterator.json_object_iterator};
        }
    }

    Json::const_iterator::const_iterator(Json::const_iterator && r_iterator) noexcept :
    iterators::JsonIterator {r_iterator.used_type} {
        if (used_type == IteratorTypes::array_iterator_type) {
            array_iterator = r_iterator.array_iterator;
            r_iterator.array_iterator = nullptr;
        } else {
            json_object_iterator = r_iterator.json_object_iterator;
            r_iterator.json_object_iterator = nullptr;
        }
    }

    // Public Methods
    Json::iterator Json::begin() {
        switch (used_type) {
            case DataType::array_type:
                return Json::iterator {data_array->begin()};
            case DataType::json_object_type:
                return Json::iterator {data_json_object->begin()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::iterator Json::end() {
        switch (used_type) {
            case DataType::array_type:
                return Json::iterator {data_array->end()};
            case DataType::json_object_type:
                return Json::iterator {data_json_object->end()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::const_iterator Json::cbegin() {
        switch (used_type) {
            case DataType::array_type:
                return Json::const_iterator {data_array->cbegin()};
            case DataType::json_object_type:
                return Json::const_iterator {data_json_object->cbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::const_iterator Json::cend() {
        switch (used_type) {
            case DataType::array_type:
                return Json::const_iterator {data_array->cend()};
            case DataType::json_object_type:
                return Json::const_iterator {data_json_object->cend()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json & Json::iterator::value() const {
        check_json_object();
        return (* json_object_iterator)->second;
    }

    const JsonKey & Json::iterator::key() const {
        check_json_object();
        return (* json_object_iterator)->first;
    }

    JsonObject & Json::items() const {
        if (used_type == DataType::json_object_type) {
            return * data_json_object;
        }
        throw iterators::exceptions::InvalidType {};
    }

    const JsonKey & Json::const_iterator::key() const {
        check_json_object();
        return (* json_object_iterator)->first;
    }

    const Json & Json::const_iterator::value() const {
        check_json_object();
        return (* json_object_iterator)->second;
    }

    // Operator Overloading
    Json & Json::iterator::operator*() const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return * * array_iterator;
        }
        throw iterators::exceptions::InvalidDereference {};
    }

    const Json::iterator Json::iterator::operator++(int) {
        Json::iterator temp {* this};
        add_to_iterator();
        return std::move(temp);
    }

    Json::iterator & Json::iterator::operator++() {
        add_to_iterator();
        return * this;
    }

    Json::iterator Json::iterator::operator+(int i) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return Json::iterator{* array_iterator + i};
        } else {
            throw exceptions::InvalidOperator {};
        }
    }

    Json::iterator Json::iterator::operator-(int i) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return Json::iterator{* array_iterator - i};
        } else {
            throw exceptions::InvalidOperator {};
        }
    }

    Json::iterator Json::iterator::operator+=(int i) {
        if (used_type == IteratorTypes::array_iterator_type) {
            * array_iterator += i;
            return * this;
        } else {
            throw exceptions::InvalidOperator {};
        }
    }

    Json::iterator Json::iterator::operator-=(int i) {
        if (used_type == IteratorTypes::array_iterator_type) {
            * array_iterator -= i;
            return * this;
        } else {
            throw exceptions::InvalidOperator {};
        }
    }

    bool Json::iterator::operator!=(const iterator & r_iterator) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return * array_iterator != * r_iterator.array_iterator;
        } else {
            return * json_object_iterator != * r_iterator.json_object_iterator;
        }
    }

    const Json & Json::const_iterator::operator*() const {
         if (used_type == IteratorTypes::array_iterator_type) {
             return * * array_iterator;
         }
         throw iterators::exceptions::InvalidDereference {};
    }

    Json::const_iterator Json::const_iterator::operator++(int) {
        Json::const_iterator temp {* this};
        add_to_iterator();
        return std::move(temp);
    }

    Json::const_iterator & Json::const_iterator::operator++() {
        add_to_iterator();
        return * this;
    }

    bool Json::const_iterator::operator!=(const const_iterator & r_iterator) const {
        if (used_type == IteratorTypes::array_iterator_type) {
            return * array_iterator == * r_iterator.array_iterator;
        }
        return * json_object_iterator == * r_iterator.json_object_iterator;
    }

    // Protected Methods
    void Json::iterator::add_to_iterator() {
        if (used_type == IteratorTypes::array_iterator_type) {
            ++ * array_iterator;
        } else {
            ++ * json_object_iterator;
        }
    }

    void Json::const_iterator::add_to_iterator() {
        if (used_type == IteratorTypes::array_iterator_type) {
            ++ * array_iterator;
        } else {
            ++ * json_object_iterator;
        }
    }

    // Destructors
    Json::iterator::~iterator() noexcept {
        if (used_type == IteratorTypes::array_iterator_type) {
            delete array_iterator;
        } else {
            delete json_object_iterator;
        }
    }

    Json::const_iterator::~const_iterator() noexcept {
        if (used_type == IteratorTypes::array_iterator_type) {
            delete array_iterator;
        } else {
            delete json_object_iterator;
        }
    }

    #pragma endregion
}
