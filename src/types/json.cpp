#include <types/json.h>
#include "types/json_patch.h"

namespace simple_json::types {
    #pragma region Functions

    namespace {
        void apply_merge_patch(Json & current_item, const Json & current_patch) noexcept {
            if (current_patch.type() == DataType::JSON_OBJECT_TYPE) {
                if (current_item.type() != DataType::JSON_OBJECT_TYPE)
                    current_item = Json (DataType::JSON_OBJECT_TYPE);
                for (auto & [key, value]: current_patch.items()) {
                    if (value.type() == DataType::NULL_TYPE) {
                        if (current_item.find(key) != current_item.end())
                            current_item.erase(key);
                    } else
                        apply_merge_patch(current_item.at(key), value);
                }
            } else
                current_item = current_patch;
        }
    }

    #pragma endregion
    #pragma region Constructors
    Json::Json(const double data) : data {data} {}

    Json::Json(const bool data) : data {data} {}

    Json::Json(const long int data) : data {data} {}

    Json::Json(const int data) : data {data} {}

    Json::Json(const char *data) : data {new std::string {data}} {}

    Json::Json(const std::nullptr_t) : data {nullptr} {}

    Json::Json(const Array & data) : data {new Array(data)} {}

    Json::Json(Array && data) : data {new Array(std::move(data))} {}

    Json::Json(const array_list_type & initializer_list) : data {new Array {initializer_list}} {}

    Json::Json(const std::string & data) : data {new std::string {data}} {}

    Json::Json(std::string && data) : data {new std::string {std::move(data)}} {}

    Json::Json(const JsonObject & data) : data {new JsonObject {data}} {}

    Json::Json(JsonObject && data) : data {new JsonObject {std::move(data)}} {}

    Json::Json(const json_list_type & initializer_list) : data {new JsonObject {initializer_list}} {}

    Json::Json(const Json & json_item) {
        copy(json_item);
    }

    Json::Json(Json && json_item) noexcept : data {json_item.data} {
        json_item.data = std::monostate {};
    }

    Json::Json() : data {new JsonObject {}} {}

    Json::Json(const DataType object_type) {
        create_object(object_type);
    }

    #pragma endregion

    #pragma region Operator Overloading

    Json & Json::operator=(const array_list_type & initializer_list) {
        clean_memory();
        data = new Array(initializer_list);
        return *this;
    }

    Json & Json::operator=(const json_list_type & initializer_list) {
        clean_memory();
        data = new JsonObject(initializer_list);
        return *this;
    }

    Json & Json::operator=(const DataType object_type) {
        clean_memory();
        create_object(object_type);
        return *this;
    }

    Json::operator long int() const {
        if (data.index() == DataType::INTEGER_TYPE)
            return std::get<DataType::INTEGER_TYPE>(data);
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::INTEGER_TYPE};
    }

    Json::operator double() const {
        switch (data.index()) {
            case DataType::DOUBLE_TYPE: return std::get<DataType::DOUBLE_TYPE>(data);
            case DataType::INTEGER_TYPE: return static_cast<double>(std::get<DataType::INTEGER_TYPE>(data));
            default:
                throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::DOUBLE_TYPE};
        }
    }

    Json::operator std::string() const {
        if (data.index() == DataType::STRING_TYPE)
            return *std::get<DataType::STRING_TYPE>(data);
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::STRING_TYPE};
    }

    Json::operator const char *() const {
        return check_type<DataType::STRING_TYPE>()->c_str();
    }

    Json::operator Array() const {
        if (data.index() == DataType::ARRAY_TYPE)
            return *std::get<DataType::ARRAY_TYPE>(data);
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::ARRAY_TYPE};
    }

    Json::operator JsonObject() const {
        if (data.index() == DataType::JSON_OBJECT_TYPE)
            return *std::get<DataType::JSON_OBJECT_TYPE>(data);
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::JSON_OBJECT_TYPE};
    }

    Json & Json::operator=(const Json &r_json) {
        clean_memory();
        copy(r_json);
        return * this;
    }

    Json & Json::operator=(Json &&r_json) noexcept {
        clean_memory();
        data = r_json.data;
        r_json.data = std::monostate {};
        return *this;
    }

    Json & Json::operator[](const size_t &index) const {
        return (*check_type<DataType::ARRAY_TYPE>())[index];
    }

    Json & Json::operator[](const char *key) const {
        return (*check_type<DataType::JSON_OBJECT_TYPE>())[JsonKey {key}];
    }

    Json & Json::operator[](const JsonKey &key) const {
        return (*check_type<DataType::JSON_OBJECT_TYPE>())[key];
    }

    Json & Json::operator[](const JsonPointer &json_pointer) const {
        can_iterate();
        const Json *tmp_return(this);
        for (const std::string & index: * json_pointer.pointer_list)
            if (tmp_return->data.index() == DataType::ARRAY_TYPE)
                if (utils::is_digit(index))
                    tmp_return = & (* std::get<DataType::ARRAY_TYPE>(
                            tmp_return->data))[strtol(index.c_str(), nullptr, 10)];
                else
                    throw exceptions::InvalidOperation {};
            else
                tmp_return = &(*std::get<DataType::JSON_OBJECT_TYPE>(tmp_return->data))[JsonKey {index}];
        return const_cast<Json &>(*tmp_return);
    }

    bool Json::operator==(const Json &json_item) const {
        if (json_item.data.index() != data.index())
            return false;
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
            case DataType::DOUBLE_TYPE:
            case DataType::BOOLEAN_TYPE:
                return data == json_item.data;
            case DataType::STRING_TYPE:
                return *std::get<DataType::STRING_TYPE>(data) == *std::get<DataType::STRING_TYPE>(json_item.data);
            case DataType::ARRAY_TYPE:
                return *std::get<DataType::ARRAY_TYPE>(data) == *std::get<DataType::ARRAY_TYPE>(json_item.data);
            case DataType::JSON_OBJECT_TYPE:
                return *std::get<DataType::JSON_OBJECT_TYPE>(data) ==
                       *std::get<DataType::JSON_OBJECT_TYPE>(json_item.data);
            default:
                return true;
        }
    }

    bool Json::operator!=(const Json & json_item) const {
        if (json_item.data.index() != data.index())
            return true;
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
            case DataType::DOUBLE_TYPE:
            case DataType::BOOLEAN_TYPE:
                return data != json_item.data;
            case DataType::STRING_TYPE:
                return *std::get<DataType::STRING_TYPE>(data) != *std::get<DataType::STRING_TYPE>(json_item.data);
            case DataType::ARRAY_TYPE:
                return *std::get<DataType::ARRAY_TYPE>(data) != *std::get<DataType::ARRAY_TYPE>(json_item.data);
            case DataType::JSON_OBJECT_TYPE:
                return *std::get<DataType::JSON_OBJECT_TYPE>(data) !=
                       *std::get<DataType::JSON_OBJECT_TYPE>(json_item.data);
            default:
                return false;
        }
    }

    const Json Json::operator++(int) {
        Json old_json(*this);
        increment();
        return old_json;
    }

    Json & Json::operator++() {
        increment();
        return *this;
    }

    const Json Json::operator--(int) {
        Json old_json(*this);
        decrement();
        return old_json;
    }

    Json & Json::operator--() {
        decrement();
        return *this;
    }

    Json Json::operator*(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            std::get<DataType::INTEGER_TYPE>(new_json.data) *= rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) *= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator*(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            new_json.data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(new_json.data)) * rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) *= rhs;
        return new_json;
    }

    Json Json::operator+(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            std::get<DataType::INTEGER_TYPE>(new_json.data) += rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) += static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator+(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            new_json.data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(new_json.data)) + rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) += rhs;
        return new_json;
    }

    Json Json::operator-(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            std::get<DataType::INTEGER_TYPE>(new_json.data) -= rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) -= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator-(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            new_json.data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(new_json.data)) - rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) -= rhs;
        return new_json;
    }

    Json Json::operator/(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            std::get<DataType::INTEGER_TYPE>(new_json.data) /= rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) /= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator/(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.data.index() == DataType::INTEGER_TYPE)
            new_json.data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(new_json.data)) / rhs;
        else
            std::get<DataType::DOUBLE_TYPE>(new_json.data) /= rhs;
        return new_json;
    }

    Json Json::operator%(long rhs) {
        return check_type<DataType::INTEGER_TYPE>() % rhs;
    }

    Json & Json::operator+=(long rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                std::get<DataType::INTEGER_TYPE>(data) += rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) = static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator+=(double rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(data)) + rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) += rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator-=(long rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                std::get<DataType::INTEGER_TYPE>(data) -= rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) -= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator-=(double rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(data)) - rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) -= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator*=(long rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                std::get<DataType::INTEGER_TYPE>(data) *= rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) *= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator*=(double rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(data)) * rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) *= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator/=(long rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                std::get<DataType::INTEGER_TYPE>(data) /= rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) /= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator/=(double rhs) {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                data = static_cast<double>(std::get<DataType::INTEGER_TYPE>(data)) / rhs;
                break;
            case DataType::DOUBLE_TYPE:
                std::get<DataType::DOUBLE_TYPE>(data) /= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator%=(long rhs) {
        check_operator(DataType::INTEGER_TYPE);
        std::get<DataType::INTEGER_TYPE>(data) %= rhs;
        return *this;
    }

    Json & Json::operator+=(int rhs) {
        return *this += static_cast<long>(rhs);
    }

    Json & Json::operator-=(int rhs) {
        return *this -= static_cast<long>(rhs);
    }

    Json & Json::operator*=(int rhs) {
        return *this *= static_cast<long>(rhs);
    }

    Json & Json::operator/=(int rhs) {
        return *this /= static_cast<long>(rhs);
    }

    Json & Json::operator%=(int rhs) {
        return *this %= static_cast<long>(rhs);
    }

    Json Json::operator*(int rhs) {
        return *this * static_cast<long>(rhs);
    }

    Json Json::operator+(int rhs) {
        return *this + static_cast<long>(rhs);
    }

    Json Json::operator-(int rhs) {
        return *this - static_cast<long>(rhs);
    }

    Json Json::operator/(int rhs) {
        return *this / static_cast<long>(rhs);
    }

    Json Json::operator%(int rhs) {
        return *this % static_cast<long>(rhs);
    }

    #pragma endregion

    #pragma region Destructor
    Json::~Json() {
        clean_memory();
    }


    #pragma endregion Destructor

    #pragma region Private Methods
    template<DataType T>
    auto Json::check_type() const -> decltype(std::get<T>(const_cast<variant_type &>(data))) {
        if (data.index() != T)
            throw exceptions::InvalidOperation {T};
        return std::get<T>(const_cast<variant_type &>(data));
    }

    void Json::clean_memory() noexcept {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                delete std::get<DataType::ARRAY_TYPE>(data);
                return;
            case DataType::JSON_OBJECT_TYPE:
                delete std::get<DataType::JSON_OBJECT_TYPE>(data);
                return;
            case DataType::STRING_TYPE:
                delete std::get<DataType::STRING_TYPE>(data);
                return;
            default:
                return;
        }
    }

    void Json::copy(const Json & json_item) {
        switch (json_item.data.index()) {
            case DataType::NULL_TYPE:
            case DataType::INTEGER_TYPE:
            case DataType::DOUBLE_TYPE:
            case DataType::BOOLEAN_TYPE:
                data = json_item.data;
                return;
            case DataType::STRING_TYPE:
                data = new std::string {*std::get<DataType::STRING_TYPE>(json_item.data)};
                return;
            case DataType::ARRAY_TYPE:
                data = new Array(*std::get<DataType::ARRAY_TYPE>(json_item.data));
                return;
            case DataType::JSON_OBJECT_TYPE:
                data = new JsonObject(*std::get<DataType::JSON_OBJECT_TYPE>(json_item.data));
                return;
            default:
                return;
        }
    }

    void Json::create_object(DataType object_type) {
        switch (object_type) {
            case DataType::UNKNOWN:
                data = std::monostate();
                return;
            case DataType::NULL_TYPE:
                data = nullptr;
                return;
            case DataType::INTEGER_TYPE:
                data = 0;
                return;
            case DataType::DOUBLE_TYPE:
                data = 0.0;
                return;
            case DataType::STRING_TYPE:
                data = new std::string {};
                return;
            case DataType::ARRAY_TYPE:
                data = new Array {};
                return;
            case DataType::JSON_OBJECT_TYPE:
                data = new JsonObject {};
                return;
            case DataType::BOOLEAN_TYPE:
                data = false;
                return;
            default:
                return;
        }
    }

    void Json::is_numeric() const {
        if (data.index() != DataType::INTEGER_TYPE && data.index() != DataType::DOUBLE_TYPE)
            throw exceptions::InvalidOperator {};
    }

    void Json::increment() {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                ++std::get<DataType::INTEGER_TYPE>(data);
                return;
            case DataType::DOUBLE_TYPE:
                ++std::get<DataType::DOUBLE_TYPE>(data);
                return;
            default:
                throw exceptions::InvalidOperator {};
        }
    }

    void Json::decrement() {
        switch (data.index()) {
            case DataType::INTEGER_TYPE:
                --std::get<DataType::INTEGER_TYPE>(data);
                return;
            case DataType::DOUBLE_TYPE:
                --std::get<DataType::DOUBLE_TYPE>(data);
                return;
            default:
                throw exceptions::InvalidOperator {};
        }
    }

    void Json::check_operator(DataType target_type) const {
        if (data.index() != target_type)
            throw exceptions::InvalidOperator {};
    }

    void Json::check_data(DataType target_type) const {
        if (data.index() != target_type)
            throw exceptions::WrongType {static_cast<DataType>(data.index())};
    }

    #pragma endregion

    #pragma region OS Overloading
    std::ostream & operator<<(std::ostream & os, const Json & json_item) {
        switch (json_item.data.index()) {
            case DataType::NULL_TYPE:
                return os << "null";
            case DataType::INTEGER_TYPE:
                return os << std::get<DataType::INTEGER_TYPE>(json_item.data);
            case DataType::DOUBLE_TYPE:
                return os << std::get<DataType::DOUBLE_TYPE>(json_item.data);
            case DataType::BOOLEAN_TYPE:
                return os << std::boolalpha << std::get<DataType::BOOLEAN_TYPE>(json_item.data) << std::noboolalpha;
            case DataType::STRING_TYPE:
                return os << * std::get<DataType::STRING_TYPE>(json_item.data);
            case DataType::ARRAY_TYPE:
                return os << * std::get<DataType::ARRAY_TYPE>(json_item.data);
            case DataType::JSON_OBJECT_TYPE:
                return os << * std::get<DataType::JSON_OBJECT_TYPE>(json_item.data);
            default:
                throw serializer::exceptions::StreamInsertionException();
        }
    }

    #pragma endregion

    #pragma region Public Methods
    std::string Json::serialize() const {
        std::string serialized {*check_type<DataType::STRING_TYPE>()};
        utils::replace_str(serialized, "\n", "\\n");
        utils::replace_str(serialized, "\t", "\\t");
        utils::replace_str(serialized, std::string {'\0'}, "\\0");
        utils::replace_str(serialized, "\b", "\\b");
        return '"' + serialized + '"';
    }

    Json::iterator Json::begin() {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::iterator {std::get<DataType::ARRAY_TYPE>(data)->begin()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->begin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::iterator Json::end() {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::iterator {std::get<DataType::ARRAY_TYPE>(data)->end()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->end()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_iterator Json::cbegin() const {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return const_iterator {std::get<DataType::ARRAY_TYPE>(data)->cbegin()};
            case DataType::JSON_OBJECT_TYPE:
                return const_iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->cbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_iterator Json::cend() const {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::const_iterator {std::get<DataType::ARRAY_TYPE>(data)->cend()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::const_iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->cend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::reverse_iterator Json::rbegin() {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::reverse_iterator {std::get<DataType::ARRAY_TYPE>(data)->rbegin()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::reverse_iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->rbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::reverse_iterator Json::rend() {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::reverse_iterator {std::get<DataType::ARRAY_TYPE>(data)->rend()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::reverse_iterator {std::get<DataType::JSON_OBJECT_TYPE>(data)->rend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_reverse_iterator Json::crbegin() const {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return const_reverse_iterator {std::get<DataType::ARRAY_TYPE>(data)->crbegin()};
            case DataType::JSON_OBJECT_TYPE:
                return const_reverse_iterator {
                    std::get<DataType::JSON_OBJECT_TYPE>(data)->crbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_reverse_iterator Json::crend() const {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return Json::const_reverse_iterator {std::get<DataType::ARRAY_TYPE>(data)->crend()};
            case DataType::JSON_OBJECT_TYPE:
                return Json::const_reverse_iterator {
                    std::get<DataType::JSON_OBJECT_TYPE>(data)->crend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    void Json::merge_patch(const Json & merge_patch) noexcept {
        apply_merge_patch(* this, merge_patch);
    }

    Json Json::merge(const Json & target) const {
        if (data.index() == DataType::ARRAY_TYPE || data.index() == DataType::JSON_OBJECT_TYPE) {
            if (data.index() != target.data.index())
                throw exceptions::InvalidMerge{static_cast<DataType>(target.data.index())};
        } else if (target.data.index() == DataType::ARRAY_TYPE || target.data.index() == DataType::JSON_OBJECT_TYPE)
            throw exceptions::InvalidMerge {};
        Json new_json(static_cast<DataType>(data.index()));
        if (data.index() == DataType::ARRAY_TYPE) {
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
            if (size() == target.size())
                return new_json;
            if (size() > target.size())
                for (i = target.size(); i < size(); ++i)
                    new_json.push_back(at(i));
            else
                for (i = size(); i < target.size(); ++i)
                    new_json.push_back(target.at(i));
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
            if (new_json.find(key) != new_json.end())
                continue;
            new_json.insert({key, value});
        }
        return new_json;
    }

    JsonPatch Json::get_diff(const Json & dst) const {
        return JsonPatch::PatchBuilder {* this, dst}.create_patch();
    }

    long & Json::get_int() {
        check_data(DataType::INTEGER_TYPE);
        return std::get<DataType::INTEGER_TYPE>(data);
    }

    double & Json::get_double() {
        check_data(DataType::DOUBLE_TYPE);
        return std::get<DataType::DOUBLE_TYPE>(data);
    }

    bool & Json::get_bool() {
        check_data(DataType::BOOLEAN_TYPE);
        return std::get<DataType::BOOLEAN_TYPE>(data);
    }

    std::string & Json::get_string() {
        check_data(DataType::STRING_TYPE);
        return * std::get<DataType::STRING_TYPE>(data);
    }

    Array & Json::get_array() {
        check_data(DataType::ARRAY_TYPE);
        return * std::get<DataType::ARRAY_TYPE>(data);
    }

    JsonObject & Json::get_json_object() {
        check_data(DataType::JSON_OBJECT_TYPE);
        return * std::get<DataType::JSON_OBJECT_TYPE>(data);
    }

    template<typename T>
    T Json::find_in_range(const T &first, const T &last, const Json &item) const {
        return T {std::find(*first.template check_type<IteratorType::ARRAY_ITERATOR_TYPE>(),
                            *last.template check_type<IteratorType::ARRAY_ITERATOR_TYPE>(), item)};
    }

    template<typename T>
    size_t Json::count_in_range(const T &first, const T &last, const Json &item) const {
        return std::count(*first.template check_type<IteratorType::ARRAY_ITERATOR_TYPE>(),
                          *last.template check_type<IteratorType::ARRAY_ITERATOR_TYPE>(), item);
    }

    void Json::update(const Json & target) {
        if (data.index() != DataType::JSON_OBJECT_TYPE || target.data.index() != DataType::JSON_OBJECT_TYPE)
            throw exceptions::InvalidOperation {DataType::JSON_OBJECT_TYPE};
        for (const pair_type & item: target.items()) {
            JsonObject *&data_json_object {std::get<DataType::JSON_OBJECT_TYPE>(data)};
            if (data_json_object->find(item.first) != data_json_object->cend()) {
                data_json_object->at(item.first) = item.second;
                continue;
            }
            data_json_object->insert(item);
        }
    }

    size_t Json::size() const noexcept {
        switch (data.index()) {
            case DataType::STRING_TYPE:
            case DataType::INTEGER_TYPE:
            case DataType::BOOLEAN_TYPE:
            case DataType::DOUBLE_TYPE:
                return 1;
            case DataType::ARRAY_TYPE:
                return std::get<DataType::ARRAY_TYPE>(data)->size();
            case DataType::JSON_OBJECT_TYPE:
                return std::get<DataType::JSON_OBJECT_TYPE>(data)->size();
            default:
                return 0;
        }
    }

    Json::iterator Json::find(const JsonKey & key) {
        return iterator {check_type<DataType::JSON_OBJECT_TYPE>()->find(key)};
    }

    Json::iterator Json::find(const Json & item) {
        if (data.index() == DataType::ARRAY_TYPE) {
            Array *&data_array {std::get<DataType::ARRAY_TYPE>(data)};
            return iterator {std::find(data_array->begin(), data_array->end(), item)};
        } else if (data.index() == DataType::JSON_OBJECT_TYPE) {
            JsonObject *&data_json_object {std::get<DataType::JSON_OBJECT_TYPE>(data)};
            return iterator { std::find_if(
                    data_json_object->begin(), data_json_object->end(), [item](const pair_type & pair_item) {
                        return pair_item.second == item;
                    }
            )};
        } else
            throw exceptions::InvalidOperation {};
    }

    Json::const_iterator Json::find(const Json & item) const {
        can_iterate();
        if (data.index() == DataType::ARRAY_TYPE) {
            Array *const &data_array {std::get<DataType::ARRAY_TYPE>(data)};
            return const_iterator {std::find(data_array->cbegin(), data_array->cend(), item)};
        } else {
            JsonObject *const &data_json_object {std::get<DataType::JSON_OBJECT_TYPE>(data)};
            return const_iterator { std::find_if(
                    data_json_object->cbegin(),
                    data_json_object->cend(), [item](const pair_type & pair_item){
                        return pair_item.second == item;
                    }
            )};
        }
    }

    Json::const_iterator Json::find(const JsonKey & key) const {
        return const_iterator {check_type<DataType::JSON_OBJECT_TYPE>()->find(key)};
    }

    Json::iterator Json::find_if(const std::function<bool(const Json &)> & test_func) {
        Array *&data_array {check_type<DataType::ARRAY_TYPE>()};
        return iterator {std::find_if(data_array->begin(), data_array->end(), test_func)};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const Json &)> & test_func) const {
        Array *const &data_array {check_type<DataType::ARRAY_TYPE>()};
        return const_iterator {
            std::find_if(data_array->cbegin(), data_array->cend(), test_func)};
    }

    Json::iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) {
        JsonObject * &data_json_object {check_type<DataType::JSON_OBJECT_TYPE>()};
        return iterator {std::find_if(
                data_json_object->begin(), data_json_object->end(), test_func
                )};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) const {
        JsonObject *const &data_json_object {check_type<DataType::JSON_OBJECT_TYPE>()};
        return const_iterator {std::find_if(data_json_object->cbegin(), data_json_object->cend(), test_func)};
    }

    size_t Json::find_index(const Json & item) const {
        Array *const &data_array {check_type<DataType::ARRAY_TYPE>()};
        return std::distance(data_array->cbegin(), std::find(data_array->cbegin(), data_array->cend(), item));
    }

    size_t Json::find_index(const const_iterator &it) const {
        return std::distance(check_type<DataType::ARRAY_TYPE>()->cbegin(),
                             *it.check_type<IteratorType::ARRAY_ITERATOR_TYPE>());
    }

    size_t Json::count(const Json & item) const {
        Array *const &data_array {check_type<DataType::ARRAY_TYPE>()};
        return std::count(data_array->cbegin(), data_array->cend(), item);
    }

    bool Json::contains(const JsonKey & key) const {
        JsonObject *const &data_json_object {check_type<DataType::JSON_OBJECT_TYPE>()};
        return data_json_object->find(key) != data_json_object->cend();
    }

    bool Json::contains(const Json & item) const {
        return find(item) != cend();
    }

    bool Json::empty() const {
        switch (data.index()) {
            case DataType::ARRAY_TYPE:
                return std::get<DataType::ARRAY_TYPE>(data)->empty();
            case DataType::JSON_OBJECT_TYPE:
                return std::get<DataType::JSON_OBJECT_TYPE>(data)->empty();
            default:
                throw exceptions::InvalidOperation {};
        }
    }

    Json & Json::at(const size_t index) const {
        return check_type<DataType::ARRAY_TYPE>()->at(index);
    }

    Json & Json::at(const std::string & index) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->at(JsonKey {index});
    }

    Json & Json::at(const JsonKey & key) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->at(key);
    }

    Json & Json::at(const JsonPointer & json_pointer) const {
        can_iterate();
        const Json * tmp_return {this};
        for (const std::string & index: * json_pointer.pointer_list)
            if (tmp_return->data.index() == DataType::ARRAY_TYPE)
                if (utils::is_digit(index))
                    tmp_return = & tmp_return->at(strtol(index.c_str(), nullptr, 10));
                else
                    throw exceptions::InvalidOperation {};
            else
                tmp_return = & tmp_return->at(index);
        return const_cast<Json &>(* tmp_return);
    }

    Json Json::get(const JsonKey & key, const Json & default_return) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->get(key, default_return);
    }

    Json Json::get(const JsonKey & key, Json && default_return) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->get(key, std::move(default_return));
    }

    Json Json::get(const std::string & key, const Json & default_return) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->get(JsonKey {key}, default_return);
    }

    Json Json::get(const std::string & key, Json && default_return) const {
        return check_type<DataType::JSON_OBJECT_TYPE>()->get(
                JsonKey {key}, std::move(default_return));
    }

    void Json::erase(long index) {
        Array *&data_array {check_type<DataType::ARRAY_TYPE>()};
        data_array->erase(data_array->cbegin() + index);
    }

    void Json::erase(const std::string &index) {
        check_type<DataType::JSON_OBJECT_TYPE>()->erase(JsonKey {index});
    }

    void Json::erase(const JsonKey &index) {
        check_type<DataType::JSON_OBJECT_TYPE>()->erase(index);
    }

    void Json::erase(const JsonPointer &json_pointer) {
        Json & target {at(json_pointer.get_parent())};
        if (target.data.index() == DataType::ARRAY_TYPE)
            target.erase(static_cast<long>(json_pointer.get_index()));
        else if (target.data.index() == DataType::JSON_OBJECT_TYPE)
            std::get<DataType::JSON_OBJECT_TYPE>(target.data)->erase(json_pointer.get_key());
        else
            throw exceptions::InvalidIndex {static_cast<DataType>(data.index())};
    }

    void Json::push_back(const Json & new_item) {
        check_type<DataType::ARRAY_TYPE>()->push_back(new_item);
    }

    void Json::insert(const pair_type & new_item) {
        check_type<DataType::JSON_OBJECT_TYPE>()->insert(new_item);
    }

    void Json::insert(pair_type && new_item) {
        check_type<DataType::JSON_OBJECT_TYPE>()->insert(std::move(new_item));
    }

    void Json::insert(const Json::const_iterator & position, const Json & item) {
        check_type<DataType::ARRAY_TYPE>()->insert(* position.check_type<IteratorType::ARRAY_ITERATOR_TYPE>(), item);
    }

    void Json::insert(const Json::const_iterator &position, Json && item) {
        check_type<DataType::ARRAY_TYPE>()->insert(* position.check_type<IteratorType::ARRAY_ITERATOR_TYPE>(),
                                                   std::move(item));
    }

    Json::const_iterator Json::get_item(const long index) const {
        return const_iterator {check_type<DataType::ARRAY_TYPE>()->cbegin() + index};
    }

    void Json::push_back(Json && new_item) {
        check_type<DataType::ARRAY_TYPE>()->push_back(std::move(new_item));
    }

    Json & Json::back() const noexcept {
        return check_type<DataType::ARRAY_TYPE>()->back();
    }

    JsonObject & Json::items() const {
        if (data.index() == DataType::JSON_OBJECT_TYPE) {
            return *std::get<DataType::JSON_OBJECT_TYPE>(data);
        }
        throw iterators::exceptions::InvalidType {};
    }

    #pragma endregion

    #pragma Explicit Template Instantiation

    template auto Json::check_type<DataType::UNKNOWN>() const -> std::monostate &;
    template auto Json::check_type<DataType::NULL_TYPE>() const -> std::nullptr_t &;
    template auto Json::check_type<DataType::INTEGER_TYPE>() const -> long int &;
    template auto Json::check_type<DataType::DOUBLE_TYPE>() const -> double &;
    template auto Json::check_type<DataType::BOOLEAN_TYPE>() const -> bool &;
    template auto Json::check_type<DataType::STRING_TYPE>() const -> std::string *&;
    template auto Json::check_type<DataType::ARRAY_TYPE>() const -> Array *&;
    template auto Json::check_type<DataType::JSON_OBJECT_TYPE>() const -> JsonObject *&;

    template Json::iterator Json::find_in_range(const Json::iterator &, const Json::iterator &, const Json &item) const;
    template Json::const_iterator Json::find_in_range(const Json::const_iterator &, const Json::const_iterator &,
            const Json &) const;
    template Json::reverse_iterator Json::find_in_range(const Json::reverse_iterator &, const Json::reverse_iterator &,
            const Json &) const;
    template Json::const_reverse_iterator Json::find_in_range(const Json::const_reverse_iterator &,
            const Json::const_reverse_iterator &, const Json &) const;

    template size_t Json::count_in_range(const Json::iterator &, const Json::iterator &, const Json &item) const;
    template size_t Json::count_in_range(const Json::const_iterator &, const Json::const_iterator &,
                                         const Json & item) const;
    template size_t Json::count_in_range(const Json::reverse_iterator &, const Json::reverse_iterator &,
            const Json &) const;
    template size_t Json::count_in_range(const Json::const_reverse_iterator &, const Json::const_reverse_iterator &,
            const Json &) const;

    #pragma endregion
}
