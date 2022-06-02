#include <types/json.h>
#include "types/json_patch.h"

namespace simple_json::types {
    #pragma region Functions

    namespace {
        void apply_merge_patch(Json & current_item, const Json & current_patch) noexcept {
            if (current_patch.type() == DataType::json_object_type) {
                if (current_item.type() != DataType::json_object_type) {
                    current_item = Json (DataType::json_object_type);
                }
                for (auto & [key, value]: current_patch.items()) {
                    if (value.type() == DataType::null_type) {
                        if (current_item.find(key) != current_item.end()) {
                            current_item.erase(key);
                        }
                    } else {
                        apply_merge_patch(current_item.at(key), value);
                    }
                }
            } else {
                current_item = current_patch;
            }
        }
    }

    #pragma endregion
    #pragma region Constructors
    Json::Json(const double data) : data_double {data}, used_type {DataType::double_type} {}

    Json::Json(const long int data) : data_int {data}, used_type {DataType::integer_type} {}

    Json::Json(const int data) : data_int {data}, used_type {DataType::integer_type} {}

    Json::Json(const bool data) : data_boolean {data}, used_type {DataType::boolean_type} {}

    Json::Json(const std::nullptr_t) : used_type(DataType::null_type) {}

    Json::Json(const Array & data) : data_array {new Array(data)},
    used_type {DataType::array_type} {}

    Json::Json(Array && data) : data_array {new Array(std::move(data))},
    used_type {DataType::array_type} {}

    Json::Json(const array_list_type & initializer_list) : data_array {new Array {initializer_list}},
    used_type(DataType::array_type) {}

    Json::Json(const std::string & data) : data_string {new std::string {data}},
    used_type {DataType::string_type} {}

    Json::Json(std::string && data) : data_string {new std::string {std::move(data)}},
    used_type {DataType::string_type} {}

    Json::Json(const char * data) : data_string {new std::string {data}}, used_type {DataType::string_type} {}

    Json::Json(const JsonObject & data) : data_json_object {new JsonObject {data}},
    used_type {DataType::json_object_type} {}

    Json::Json(JsonObject && data) : data_json_object {new JsonObject {std::move(data)}},
    used_type {DataType::json_object_type} {}

    Json::Json(const json_list_type & initializer_list) : data_json_object {new JsonObject {initializer_list}},
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

    Json & Json::operator=(const array_list_type & initializer_list) {
        clean_memory();
        used_type = DataType::array_type;
        data_array = new Array(initializer_list);
        return * this;
    }

    Json & Json::operator=(const json_list_type & initializer_list) {
        clean_memory();
        used_type = DataType::json_object_type;
        data_json_object = new JsonObject(initializer_list);
        return * this;
    }

    Json & Json::operator=(const DataType object_type) {
        clean_memory();
        used_type = object_type;
        create_object();
        return * this;
    }

    Json::operator long int() const {
        if (used_type == DataType::integer_type) {
            return data_int;
        }
        throw exceptions::BadConversion {used_type, DataType::integer_type};
    }

    Json::operator double() const {
        switch (used_type) {
            case DataType::double_type: return data_double;
            case DataType::integer_type: return static_cast<double>(data_int);
            default:
                throw exceptions::BadConversion {used_type, DataType::double_type};
        }
    }

    Json::operator std::string() const {
        if (used_type == DataType::string_type) {
            return * data_string;
        }
        throw exceptions::BadConversion {used_type, DataType::string_type};
    }

    Json::operator const char *() const {
        check_type(DataType::string_type);
        return data_string->c_str();
    }

    Json::operator Array() const {
        if (used_type == DataType::array_type) {
            return * data_array;
        }
        throw exceptions::BadConversion {used_type, DataType::array_type};
    }

    Json::operator JsonObject() const {
        if (used_type == DataType::json_object_type) {
            return * data_json_object;
        }
        throw exceptions::BadConversion {used_type, DataType::json_object_type};
    }

    Json & Json::operator=(const Json & data) {
        clean_memory();
        used_type = data.used_type;
        copy(data);
        return * this;
    }

    Json & Json::operator=(Json && data) noexcept {
        clean_memory();
        used_type = data.used_type;
        move(data);
        return * this;
    }

    Json & Json::operator[](const size_t & index) const {
        check_type(DataType::array_type);
        return (* data_array)[index];
    }

    Json & Json::operator[](const char * key) const {
        check_type(DataType::json_object_type);
        return (* data_json_object)[JsonKey {key}];
    }

    Json & Json::operator[](const JsonKey & key) const {
        check_type(DataType::json_object_type);
        return (* data_json_object)[key];
    }

    Json & Json::operator[](const JsonPointer & json_pointer) const {
        can_iterate();
        const Json * tmp_return(this);
        for (const std::string & index: * json_pointer.pointer_list) {
            if (tmp_return->used_type == DataType::array_type) {
                if (utils::is_digit(index)) {
                    tmp_return = & (* tmp_return->data_array)[strtol(index.c_str(), nullptr, 10)];
                } else {
                    throw exceptions::InvalidOperation {};
                }
            } else {
                tmp_return = & (* tmp_return->data_json_object)[JsonKey {index}];
            }
        }
        return const_cast<Json &>(* tmp_return);
    }

    bool Json::operator==(const Json & json_item) const {
        if (json_item.used_type != used_type) {
            return false;
        }
        switch (used_type) {
            case DataType::integer_type:
                return data_int == json_item.data_int;
            case DataType::string_type:
                return * data_string == * json_item.data_string;
            case DataType::double_type:
                return data_double == json_item.data_double;
            case DataType::boolean_type:
                return data_boolean == json_item.data_boolean;
            case DataType::array_type:
                return * data_array == * json_item.data_array;
            case DataType::json_object_type:
                return * data_json_object == * json_item.data_json_object;
            default:
                return true;
        }
    }

    bool Json::operator!=(const Json & json_item) const {
        if (json_item.used_type != used_type) {
            return true;
        }
        switch (used_type) {
            case DataType::integer_type:
                return data_int != json_item.data_int;
            case DataType::string_type:
                return * data_string != * json_item.data_string;
            case DataType::double_type:
                return data_double != json_item.data_double;
            case DataType::boolean_type:
                return data_boolean != json_item.data_boolean;
            case DataType::array_type:
                return * data_array != * json_item.data_array;
            case DataType::json_object_type:
                return * data_json_object != * json_item.data_json_object;
            default:
                return false;
        }
    }

    const Json Json::operator++(int) {
        Json old_json(* this);
        increment();
        return old_json;
    }

    Json & Json::operator++() {
        increment();
        return * this;
    }

    const Json Json::operator--(int) {
        Json old_json(* this);
        decrement();
        return old_json;
    }

    Json & Json::operator--() {
        decrement();
        return * this;
    }

    Json Json::operator*(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.data_int *= rhs;
        } else {
            new_json.data_double *= static_cast<double>(rhs);
        }
        return new_json;
    }

    Json Json::operator*(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.used_type = DataType::double_type;
            new_json.data_double = static_cast<double>(new_json.data_int) * new_json.data_double;
        } else {
            new_json.data_double *= rhs;
        }
        return new_json;
    }

    Json Json::operator+(long rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.data_int += rhs;
        } else {
            new_json.data_double += static_cast<double>(rhs);
        }
        return new_json;
    }

    Json Json::operator+(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.used_type = DataType::double_type;
            new_json.data_double = static_cast<double>(new_json.data_int) + rhs;
        } else {
            new_json.data_double += rhs;
        }
        return new_json;
    }

    Json Json::operator-(long rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.data_int -= rhs;
        } else {
            new_json.data_double -= static_cast<double>(rhs);
        }
        return new_json;
    }

    Json Json::operator-(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.used_type = DataType::double_type;
            new_json.data_double = static_cast<double>(new_json.data_int) - rhs;
        } else {
            new_json.data_double -= rhs;
        }
        return new_json;
    }

    Json Json::operator/(long rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.data_int /= rhs;
        } else {
            new_json.data_double /= static_cast<double>(rhs);
        }
        return new_json;
    }

    Json Json::operator/(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.used_type == DataType::integer_type) {
            new_json.used_type = DataType::double_type;
            new_json.data_double = static_cast<double>(new_json.data_int) / rhs;
        } else {
            new_json.data_double /= rhs;
        }
        return new_json;
    }

    Json Json::operator%(long rhs) {
        check_type(DataType::integer_type);
        return data_int % rhs;
    }

    Json & Json::operator+=(long rhs) {
        switch (used_type) {
            case DataType::integer_type:
                data_int += rhs;
                break;
            case DataType::double_type:
                data_double = static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator+=(double rhs) {
        switch (used_type) {
            case DataType::integer_type:
                used_type = DataType::double_type;
                data_double = static_cast<double>(data_int) + rhs;
                break;
            case DataType::double_type:
                data_double += rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator-=(long rhs) {
        switch (used_type) {
            case DataType::integer_type:
                data_int -= rhs;
                break;
            case DataType::double_type:
                data_double -= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator-=(double rhs) {
        switch (used_type) {
            case DataType::integer_type:
                used_type = DataType::double_type;
                data_double = static_cast<double>(data_int) - rhs;
                break;
            case DataType::double_type:
                data_double -= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator*=(long rhs) {
        switch (used_type) {
            case DataType::integer_type:
                data_int *= rhs;
                break;
            case DataType::double_type:
                data_double *= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator*=(double rhs) {
        switch (used_type) {
            case DataType::integer_type:
                used_type = DataType::double_type;
                data_double = static_cast<double>(data_int) * rhs;
                break;
            case DataType::double_type:
                data_double *= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator/=(long rhs) {
        switch (used_type) {
            case DataType::integer_type:
                data_int /= rhs;
                break;
            case DataType::double_type:
                data_double /= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator/=(double rhs) {
        switch (used_type) {
            case DataType::integer_type:
                used_type = DataType::double_type;
                data_double = static_cast<double>(data_int) / rhs;
                break;
            case DataType::double_type:
                data_double /= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return * this;
    }

    Json & Json::operator%=(long rhs) {
        check_operator(DataType::integer_type);
        data_int %= rhs;
        return * this;
    }

    Json & Json::operator+=(int rhs) {
        return * this += static_cast<long>(rhs);
    }

    Json & Json::operator-=(int rhs) {
        return * this -= static_cast<long>(rhs);
    }

    Json & Json::operator*=(int rhs) {
        return * this *= static_cast<long>(rhs);
    }

    Json & Json::operator/=(int rhs) {
        return * this /= static_cast<long>(rhs);
    }

    Json & Json::operator%=(int rhs) {
        return * this %= static_cast<long>(rhs);
    }

    Json Json::operator*(int rhs) {
        return * this * static_cast<long>(rhs);
    }

    Json Json::operator+(int rhs) {
        return * this + static_cast<long>(rhs);
    }

    Json Json::operator-(int rhs) {
        return * this - static_cast<long>(rhs);
    }

    Json Json::operator/(int rhs) {
        return * this / static_cast<long>(rhs);
    }

    Json Json::operator%(int rhs) {
        return * this % static_cast<long>(rhs);
    }

    #pragma endregion

    #pragma region Destructor
    Json::~Json() {
        clean_memory();
    }


    #pragma endregion Destructor

    #pragma region Private Methods
    void Json::clean_memory() noexcept {
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

    void Json::check_type(const DataType target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidOperation {target_type};
        }
    }

    void Json::is_numeric() const {
        if (used_type != DataType::integer_type && used_type != DataType::double_type) {
            throw exceptions::InvalidOperator {};
        }
    }

    void Json::increment() {
        switch (used_type) {
            case DataType::integer_type:
                ++data_int;
                return;
            case DataType::double_type:
                ++data_double;
                return;
            default:
                throw exceptions::InvalidOperator {};
        }
    }

    void Json::decrement() {
        switch (used_type) {
            case DataType::integer_type:
                --data_int;
                return;
            case DataType::double_type:
                --data_double;
                return;
            default:
                throw exceptions::InvalidOperator {};
        }
    }

    void Json::check_operator(DataType target_type) const {
        if (used_type != target_type) {
            throw exceptions::InvalidOperator {};
        }
    }

    void Json::check_data(DataType target_type) const {
        if (used_type != target_type) {
            throw exceptions::WrongType {used_type};
        }
    }

    #pragma endregion

    #pragma region OS Overloading
    std::ostream & operator<<(std::ostream & os, const Json & json_item) {
        switch (json_item.used_type) {
            case DataType::integer_type:
                return os << json_item.data_int;
            case DataType::string_type:
                return os << * (json_item.data_string);
            case DataType::double_type:
                return os << json_item.data_double;
            case DataType::boolean_type:
                return os << std::boolalpha << json_item.data_boolean << std::noboolalpha;
            case DataType::array_type:
                return os << * json_item.data_array;
            case DataType::json_object_type:
                return os << * json_item.data_json_object;
            case DataType::null_type:
                return os << "null";
            default:
                throw serializer::exceptions::StreamInsertionException();
        }
    }

    #pragma endregion

    #pragma region Public Methods
    std::string Json::serialize() const {
        check_type(DataType::string_type);
        std::string serialized(* data_string);
        utils::replace_str(serialized, "\n", "\\n");
        utils::replace_str(serialized, "\t", "\\t");
        utils::replace_str(serialized, std::string {'\0'}, "\\0");
        utils::replace_str(serialized, "\b", "\\b");
        return '"' + serialized + '"';
    }

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

    Json::const_iterator Json::cbegin() const {
        switch (used_type) {
            case DataType::array_type:
                return const_iterator {data_array->cbegin()};
            case DataType::json_object_type:
                return const_iterator {data_json_object->cbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::const_iterator Json::cend() const {
        switch (used_type) {
            case DataType::array_type:
                return Json::const_iterator {data_array->cend()};
            case DataType::json_object_type:
                return Json::const_iterator {data_json_object->cend()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::reverse_iterator Json::rbegin() {
        switch (used_type) {
            case DataType::array_type:
                return Json::reverse_iterator {data_array->rbegin()};
            case DataType::json_object_type:
                return Json::reverse_iterator {data_json_object->rbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::reverse_iterator Json::rend() {
        switch (used_type) {
            case DataType::array_type:
                return Json::reverse_iterator {data_array->rend()};
            case DataType::json_object_type:
                return Json::reverse_iterator {data_json_object->rend()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::const_reverse_iterator Json::crbegin() const {
        switch (used_type) {
            case DataType::array_type:
                return const_reverse_iterator {data_array->crbegin()};
            case DataType::json_object_type:
                return const_reverse_iterator {data_json_object->crbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    Json::const_reverse_iterator Json::crend() const {
        switch (used_type) {
            case DataType::array_type:
                return Json::const_reverse_iterator {data_array->crend()};
            case DataType::json_object_type:
                return Json::const_reverse_iterator {data_json_object->crend()};
            default:
                throw iterators::exceptions::InvalidIteration {used_type};
        }
    }

    void Json::merge_patch(const Json & merge_patch) noexcept {
        apply_merge_patch(* this, merge_patch);
    }

    Json Json::merge(const Json & target) const {
        if (used_type == DataType::array_type || used_type == DataType::json_object_type) {
            if (used_type != target.used_type) {
                throw exceptions::InvalidMerge {target.used_type};
            }
        } else if (target.used_type == DataType::array_type || target.used_type == DataType::json_object_type) {
            throw exceptions::InvalidMerge {};
        }
        Json new_json(used_type);
        if (used_type == DataType::array_type) {
            size_t i;
            for (i = 0; i < size() && i < target.size(); ++i) {
                const Json & src_item {at(i)};
                const Json & dst_item {target.at(i)};
                if (src_item == dst_item) {
                    new_json.push_back(src_item);
                    continue;
                }
                new_json.push_back(dst_item);
            }
            if (size() == target.size()) {
                return new_json;
            }
            if (size() > target.size()) {
                for (i = target.size(); i < size(); ++i) {
                    new_json.push_back(at(i));
                }
            } else {
                for (i = size(); i < target.size(); ++i) {
                    new_json.push_back(target.at(i));
                }
            }
            return new_json;
        }
        for (const auto & [key, value]: items()) {
            if (target.find(key) != target.cend()) {
                const Json & dst_item {target.at(key)};
                if (value != dst_item) {
                    new_json.insert({key, dst_item});
                    continue;
                }
            }
            new_json.insert({key, value});
        }
        for (const auto & [key, value]: target.items()) {
            if (new_json.find(key) != new_json.end()) {
                continue;
            }
            new_json.insert({key, value});
        }
        return new_json;
    }

    JsonPatch Json::get_diff(const Json & dst) const {
        return JsonPatch::PatchBuilder {* this, dst}.create_patch();
    }

    long & Json::get_int() {
        check_data(DataType::integer_type);
        return data_int;
    }

    double & Json::get_double() {
        check_data(DataType::double_type);
        return data_double;
    }

    bool & Json::get_bool() {
        check_data(DataType::boolean_type);
        return data_boolean;
    }

    std::string & Json::get_string() {
        check_data(DataType::string_type);
        return * data_string;
    }

    Array & Json::get_array() {
        check_data(DataType::array_type);
        return * data_array;
    }

    JsonObject & Json::get_json_object() {
        check_data(DataType::json_object_type);
        return * data_json_object;
    }

    void Json::update(const Json & target) {
        if (used_type != DataType::json_object_type || target.used_type != DataType::json_object_type) {
            throw exceptions::InvalidOperation {DataType::json_object_type};
        }
        for (const pair_type & item: target.items()) {
            if (data_json_object->find(item.first) != data_json_object->cend()) {
                data_json_object->at(item.first) = item.second;
                continue;
            }
            data_json_object->insert(item);
        }
    }

    size_t Json::size() const noexcept {
        switch (used_type) {
            case DataType::string_type:
            case DataType::integer_type:
            case DataType::double_type:
                return 1;
            case DataType::array_type:
                return data_array->size();
            case DataType::json_object_type:
                return data_json_object->size();
            default:
                return 0;
        }
    }

    Json::iterator Json::find(const JsonKey & key) {
        check_type(DataType::json_object_type);
        return iterator {data_json_object->find(key)};
    }

    Json::iterator Json::find(const Json & item) {
        if (used_type == DataType::array_type) {
            return iterator {std::find(data_array->begin(), data_array->end(), item)};
        } else if (used_type == DataType::json_object_type) {
            return iterator { std::find_if(
                    data_json_object->begin(), data_json_object->end(), [item](const pair_type & pair_item) {
                        return pair_item.second == item;
                    }
            )};
        } else {
            throw exceptions::InvalidOperation {};
        }
    }

    Json::const_iterator Json::find(const Json & item) const {
        can_iterate();
        if (used_type == DataType::array_type) {
            return const_iterator {std::find(data_array->cbegin(), data_array->cend(), item)};
        } else {
            return const_iterator { std::find_if(
                    data_json_object->cbegin(), data_json_object->cend(), [item](const pair_type & pair_item){
                        return pair_item.second == item;
                    }
            )};
        }
    }

    Json::const_iterator Json::find(const JsonKey & key) const {
        check_type(DataType::json_object_type);
        return const_iterator {data_json_object->find(key)};
    }

    Json::iterator Json::find_if(const std::function<bool(const Json &)> & test_func) {
        check_type(DataType::array_type);
        return iterator {std::find_if(data_array->begin(), data_array->end(), test_func)};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const Json &)> & test_func) const {
        check_type(DataType::array_type);
        return const_iterator {std::find_if(data_array->cbegin(), data_array->cend(), test_func)};
    }

    Json::iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) {
        check_type(DataType::json_object_type);
        return iterator {std::find_if(
                data_json_object->begin(), data_json_object->end(), test_func
                )};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) const {
        check_type(DataType::json_object_type);
        return const_iterator {std::find_if(
                data_json_object->cbegin(), data_json_object->cend(), test_func
                )};
    }

    size_t Json::find_index(const Json & item) const {
        return std::distance(
                data_array->cbegin(), std::find(data_array->cbegin(), data_array->cend(), item)
            );
    }

    size_t Json::find_index(const const_iterator & it) const {
        check_type(DataType::array_type);
        if (it.used_type != IteratorTypes::array_iterator_type) {
            throw iterators::exceptions::InvalidType{};
        }
        return std::distance(data_array->cbegin(), *it.array_iterator);
    }

    size_t Json::count(const Json & item) const {
        check_type(DataType::array_type);
        return std::count(data_array->cbegin(), data_array->cend(), item);
    }

    bool Json::contains(const JsonKey & key) const {
        check_type(DataType::json_object_type);
        return data_json_object->find(key) != data_json_object->cend();
    }

    bool Json::contains(const Json & item) const {
        return find(item) != cend();
    }

    bool Json::empty() const {
        switch (used_type) {
            case DataType::array_type:
                return data_array->empty();
            case DataType::json_object_type:
                return data_json_object->empty();
            default:
                throw exceptions::InvalidOperation {};
        }
    }

    Json & Json::at(const size_t index) const {
        check_type(DataType::array_type);
        return data_array->at(index);
    }

    Json & Json::at(const std::string & index) const {
        check_type(DataType::json_object_type);
        return data_json_object->at(JsonKey {index});
    }

    Json & Json::at(const JsonKey & key) const {
        check_type(DataType::json_object_type);
        return data_json_object->at(key);
    }

    Json & Json::at(const JsonPointer & json_pointer) const {
        can_iterate();
        const Json * tmp_return {this};
        for (const std::string & index: * json_pointer.pointer_list) {
            if (tmp_return->used_type == DataType::array_type) {
                if (utils::is_digit(index)) {
                    tmp_return = & tmp_return->at(strtol(index.c_str(), nullptr, 10));
                } else {
                    throw exceptions::InvalidOperation {};
                }
            } else {
                tmp_return = & tmp_return->at(index);
            }
        }
        return const_cast<Json &>(* tmp_return);
    }

    Json Json::get(const JsonKey & key, const Json & default_return) const {
        check_type(DataType::json_object_type);
        return data_json_object->get(key, default_return);
    }

    Json Json::get(const JsonKey & key, Json && default_return) const {
        check_type(DataType::json_object_type);
        return data_json_object->get(key, std::move(default_return));
    }

    Json Json::get(const std::string & key, const Json & default_return) const {
        check_type(DataType::json_object_type);
        return data_json_object->get(JsonKey {key}, default_return);
    }

    Json Json::get(const std::string & key, Json && default_return) const {
        check_type(DataType::json_object_type);
        return data_json_object->get(JsonKey {key}, std::move(default_return));
    }

    void Json::erase(long index) {
        check_type(DataType::array_type);
        data_array->erase(data_array->cbegin() + index);
    }

    void Json::erase(const std::string & index) {
        check_type(DataType::json_object_type);
        data_json_object->erase(JsonKey {index});
    }

    void Json::erase(const JsonKey & index) {
        check_type(DataType::json_object_type);
        data_json_object->erase(index);
    }

    void Json::erase(const JsonPointer & json_pointer) {
        Json & target {at(json_pointer.get_parent())};
        if (target.used_type == DataType::array_type) {
            target.erase(static_cast<long>(json_pointer.get_index()));
        } else if (target.used_type == DataType::json_object_type){
            target.data_json_object->erase(json_pointer.get_key());
        } else {
            throw exceptions::InvalidIndex {used_type};
        }
    }

    void Json::push_back(const Json & new_item) {
        check_type(DataType::array_type);
        data_array->push_back(new_item);
    }

    void Json::insert(const pair_type & new_item) {
        check_type(DataType::json_object_type);
        data_json_object->insert(new_item);
    }

    void Json::insert(pair_type && new_item) {
        check_type(DataType::json_object_type);
        data_json_object->insert(std::move(new_item));
    }

    void Json::insert(const Json::const_iterator & position, const Json & item) {
        check_type(DataType::array_type);
        data_array->insert(* position.array_iterator, item);
    }

    void Json::insert(const Json::const_iterator & position, Json && item) {
        check_type(DataType::array_type);
        data_array->insert(* position.array_iterator, std::move(item));
    }

    Json::const_iterator Json::get_item(const long index) const {
        check_type(DataType::array_type);
        return const_iterator {data_array->cbegin() + index};
    }

    void Json::push_back(Json && new_item) {
        check_type(DataType::array_type);
        data_array->push_back(std::move(new_item));
    }

    Json & Json::back() const noexcept {
        check_type(DataType::array_type);
        return data_array->back();
    }

    JsonObject & Json::items() const {
        if (used_type == DataType::json_object_type) {
            return * data_json_object;
        }
        throw iterators::exceptions::InvalidType {};
    }

    #pragma endregion
}
