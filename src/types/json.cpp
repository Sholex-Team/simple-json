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
    template<typename T>
    Json::Json(T data) : data {data} {}

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
        if (data.index() == DataType::integer_type) {
            return std::get<DataType::integer_type>(data);
        }
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::integer_type};
    }

    Json::operator double() const {
        switch (data.index()) {
            case DataType::double_type: return std::get<DataType::double_type>(data);
            case DataType::integer_type: return static_cast<double>(std::get<DataType::integer_type>(data));
            default:
                throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::double_type};
        }
    }

    Json::operator std::string() const {
        if (data.index() == DataType::string_type) {
            return *std::get<DataType::string_type>(data);
        }
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::string_type};
    }

    Json::operator const char *() const {
        return check_type<DataType::string_type>()->c_str();
    }

    Json::operator Array() const {
        if (data.index() == DataType::array_type) {
            return *std::get<DataType::array_type>(data);
        }
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::array_type};
    }

    Json::operator JsonObject() const {
        if (data.index() == DataType::json_object_type) {
            return *std::get<DataType::json_object_type>(data);
        }
        throw exceptions::BadConversion {static_cast<DataType>(data.index()), DataType::json_object_type};
    }

    Json & Json::operator=(const Json &r_json) {
        clean_memory();
        copy(data);
        return * this;
    }

    Json & Json::operator=(Json &&r_json) noexcept {
        clean_memory();
        data = r_json.data;
        r_json.data = std::monostate {};
        return *this;
    }

    Json & Json::operator[](const size_t &index) const {
        return (*check_type<DataType::array_type>())[index];
    }

    Json & Json::operator[](const char *key) const {
        return (*check_type<DataType::json_object_type>())[JsonKey {key}];
    }

    Json & Json::operator[](const JsonKey &key) const {
        return (*check_type<DataType::json_object_type>())[key];
    }

    Json & Json::operator[](const JsonPointer &json_pointer) const {
        can_iterate();
        const Json *tmp_return(this);
        for (const std::string & index: * json_pointer.pointer_list) {
            if (tmp_return->data.index() == DataType::array_type) {
                if (utils::is_digit(index)) {
                    tmp_return = & (* std::get<DataType::array_type>(
                            tmp_return->data))[strtol(index.c_str(), nullptr, 10)];
                } else {
                    throw exceptions::InvalidOperation {};
                }
            } else {
                tmp_return = & (* std::get<DataType::json_object_type>(tmp_return->data))[JsonKey {index}];
            }
        }
        return const_cast<Json &>(* tmp_return);
    }

    bool Json::operator==(const Json &json_item) const {
        if (json_item.data.index() != data.index())
            return false;
        switch (data.index()) {
            case DataType::integer_type:
            case DataType::double_type:
            case DataType::boolean_type:
                return data == json_item.data;
            case DataType::string_type:
                return *std::get<DataType::string_type>(data) == *std::get<DataType::string_type>(json_item.data);
            case DataType::array_type:
                return *std::get<DataType::array_type>(data) == *std::get<DataType::array_type>(json_item.data);
            case DataType::json_object_type:
                return *std::get<DataType::json_object_type>(data) ==
                        *std::get<DataType::json_object_type>(json_item.data);
            default:
                return true;
        }
    }

    bool Json::operator!=(const Json & json_item) const {
        if (json_item.data.index() != data.index())
            return true;
        switch (data.index()) {
            case DataType::integer_type:
            case DataType::double_type:
            case DataType::boolean_type:
                return data != json_item.data;
            case DataType::string_type:
                return *std::get<DataType::string_type>(data) != *std::get<DataType::string_type>(json_item.data);
            case DataType::array_type:
                return *std::get<DataType::array_type>(data) != *std::get<DataType::array_type>(json_item.data);
            case DataType::json_object_type:
                return *std::get<DataType::json_object_type>(data) !=
                       *std::get<DataType::json_object_type>(json_item.data);
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
        return * this;
    }

    const Json Json::operator--(int) {
        Json old_json(*this);
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
        if (new_json.data.index() == DataType::integer_type)
            std::get<DataType::integer_type>(new_json.data) *= rhs;
        else
            std::get<DataType::double_type>(new_json.data) *= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator*(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            new_json.data = static_cast<double>(std::get<DataType::integer_type>(new_json.data)) * rhs;
        else
            std::get<DataType::double_type>(new_json.data) *= rhs;
        return new_json;
    }

    Json Json::operator+(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            std::get<DataType::integer_type>(new_json.data) += rhs;
        else
            std::get<DataType::double_type>(new_json.data) += static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator+(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            new_json.data = static_cast<double>(std::get<DataType::integer_type>(new_json.data)) + rhs;
        else
            std::get<DataType::double_type>(new_json.data) += rhs;
        return new_json;
    }

    Json Json::operator-(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            std::get<DataType::integer_type>(new_json.data) -= rhs;
        else
            std::get<DataType::double_type>(new_json.data) -= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator-(double rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            new_json.data = static_cast<double>(std::get<DataType::integer_type>(new_json.data)) - rhs;
        else
            std::get<DataType::double_type>(new_json.data) -= rhs;
        return new_json;
    }

    Json Json::operator/(long rhs) {
        is_numeric();
        Json new_json(*this);
        if (new_json.data.index() == DataType::integer_type)
            std::get<DataType::integer_type>(new_json.data) /= rhs;
        else
            std::get<DataType::double_type>(new_json.data) /= static_cast<double>(rhs);
        return new_json;
    }

    Json Json::operator/(double rhs) {
        is_numeric();
        Json new_json(* this);
        if (new_json.data.index() == DataType::integer_type)
            new_json.data = static_cast<double>(std::get<DataType::integer_type>(new_json.data)) / rhs;
        else
            std::get<DataType::double_type>(new_json.data) /= rhs;
        return new_json;
    }

    Json Json::operator%(long rhs) {
        return check_type<DataType::integer_type>() % rhs;
    }

    Json & Json::operator+=(long rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                std::get<DataType::integer_type>(data) += rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) = static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator+=(double rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                data = static_cast<double>(std::get<DataType::integer_type>(data)) + rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) += rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator-=(long rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                std::get<DataType::integer_type>(data) -= rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) -= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator-=(double rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                data = static_cast<double>(std::get<DataType::integer_type>(data)) - rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) -= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator*=(long rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                std::get<DataType::integer_type>(data) *= rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) *= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator*=(double rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                data = static_cast<double>(std::get<DataType::integer_type>(data)) * rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) *= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator/=(long rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                std::get<DataType::integer_type>(data) /= rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) /= static_cast<double>(rhs);
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator/=(double rhs) {
        switch (data.index()) {
            case DataType::integer_type:
                data = static_cast<double>(std::get<DataType::integer_type>(data)) / rhs;
                break;
            case DataType::double_type:
                std::get<DataType::double_type>(data) /= rhs;
                break;
            default:
                throw exceptions::InvalidOperator {};
        }
        return *this;
    }

    Json & Json::operator%=(long rhs) {
        check_operator(DataType::integer_type);
        std::get<DataType::integer_type>(data) %= rhs;
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
    void Json::clean_memory() noexcept {
        switch (data.index()) {
            case DataType::array_type:
                delete std::get<DataType::array_type>(data);
                return;
            case DataType::json_object_type:
                delete std::get<DataType::json_object_type>(data);
                return;
            case DataType::string_type:
                delete std::get<DataType::string_type>(data);
                return;
            default:
                return;
        }
    }

    void Json::copy(const Json & json_item) {
        switch (json_item.data.index()) {
            case DataType::null_type:
            case DataType::integer_type:
            case DataType::double_type:
            case DataType::boolean_type:
                data = json_item.data;
            case DataType::string_type:
                data = new std::string {*std::get<DataType::string_type>(json_item.data)};
                return;
            case DataType::array_type:
                data = new Array(*std::get<DataType::array_type>(json_item.data));
                return;
            case DataType::json_object_type:
                data = new JsonObject(*std::get<DataType::json_object_type>(json_item.data));
                return;
            default:
                return;
        }
    }

    void Json::create_object(DataType object_type) {
        switch (object_type) {
            case DataType::null_type:
                data = nullptr;
            case DataType::integer_type:
                data = 0;
                return;
            case DataType::double_type:
                data = 0.0;
                return;
            case DataType::string_type:
                data = new std::string {};
                return;
            case DataType::array_type:
                data = new Array {};
                return;
            case DataType::json_object_type:
                data = new JsonObject {};
                return;
            case DataType::boolean_type:
                data = false;
                return;
            default:
                return;
        }
    }

    void Json::is_numeric() const {
        if (data.index() != DataType::integer_type && data.index() != DataType::double_type) {
            throw exceptions::InvalidOperator {};
        }
    }

    void Json::increment() {
        switch (data.index()) {
            case DataType::integer_type:
                ++std::get<DataType::integer_type>(data);
                return;
            case DataType::double_type:
                ++std::get<DataType::double_type>(data);
                return;
            default:
                throw exceptions::InvalidOperator {};
        }
    }

    void Json::decrement() {
        switch (data.index()) {
            case DataType::integer_type:
                --std::get<DataType::integer_type>(data);
                return;
            case DataType::double_type:
                --std::get<DataType::double_type>(data);
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
        if (data.index() != target_type) {
            throw exceptions::WrongType {static_cast<DataType>(data.index())};
        }
    }

    #pragma endregion

    #pragma region OS Overloading
    std::ostream & operator<<(std::ostream & os, const Json & json_item) {
        switch (json_item.data.index()) {
            case DataType::null_type:
                return os << "null";
            case DataType::integer_type:
                return os << std::get<DataType::integer_type>(json_item.data);
            case DataType::double_type:
                return os << std::get<DataType::double_type>(json_item.data);
            case DataType::boolean_type:
                return os << std::boolalpha << std::get<DataType::boolean_type>(json_item.data) << std::noboolalpha;
            case DataType::string_type:
                return os << * std::get<DataType::string_type>(json_item.data);
            case DataType::array_type:
                return os << * std::get<DataType::array_type>(json_item.data);
            case DataType::json_object_type:
                return os << * std::get<DataType::json_object_type>(json_item.data);
            default:
                throw serializer::exceptions::StreamInsertionException();
        }
    }

    #pragma endregion

    #pragma region Public Methods
    std::string Json::serialize() const {
        std::string serialized {*check_type<DataType::string_type>()};
        utils::replace_str(serialized, "\n", "\\n");
        utils::replace_str(serialized, "\t", "\\t");
        utils::replace_str(serialized, std::string {'\0'}, "\\0");
        utils::replace_str(serialized, "\b", "\\b");
        return '"' + serialized + '"';
    }

    Json::iterator Json::begin() {
        switch (data.index()) {
            case DataType::array_type:
                return Json::iterator {std::get<DataType::array_type>(data)->begin()};
            case DataType::json_object_type:
                return Json::iterator {std::get<DataType::json_object_type>(data)->begin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::iterator Json::end() {
        switch (data.index()) {
            case DataType::array_type:
                return Json::iterator {std::get<DataType::array_type>(data)->end()};
            case DataType::json_object_type:
                return Json::iterator {std::get<DataType::json_object_type>(data)->end()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_iterator Json::cbegin() const {
        switch (data.index()) {
            case DataType::array_type:
                return const_iterator {std::get<DataType::array_type>(data)->cbegin()};
            case DataType::json_object_type:
                return const_iterator {std::get<DataType::json_object_type>(data)->cbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_iterator Json::cend() const {
        switch (data.index()) {
            case DataType::array_type:
                return Json::const_iterator {std::get<DataType::array_type>(data)->cend()};
            case DataType::json_object_type:
                return Json::const_iterator {std::get<DataType::json_object_type>(data)->cend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::reverse_iterator Json::rbegin() {
        switch (data.index()) {
            case DataType::array_type:
                return Json::reverse_iterator {std::get<DataType::array_type>(data)->rbegin()};
            case DataType::json_object_type:
                return Json::reverse_iterator {std::get<DataType::json_object_type>(data)->rbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::reverse_iterator Json::rend() {
        switch (data.index()) {
            case DataType::array_type:
                return Json::reverse_iterator {std::get<DataType::array_type>(data)->rend()};
            case DataType::json_object_type:
                return Json::reverse_iterator {std::get<DataType::json_object_type>(data)->rend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_reverse_iterator Json::crbegin() const {
        switch (data.index()) {
            case DataType::array_type:
                return const_reverse_iterator {std::get<DataType::array_type>(data)->crbegin()};
            case DataType::json_object_type:
                return const_reverse_iterator {
                    std::get<DataType::json_object_type>(data)->crbegin()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    Json::const_reverse_iterator Json::crend() const {
        switch (data.index()) {
            case DataType::array_type:
                return Json::const_reverse_iterator {std::get<DataType::array_type>(data)->crend()};
            case DataType::json_object_type:
                return Json::const_reverse_iterator {
                    std::get<DataType::json_object_type>(data)->crend()};
            default:
                throw iterators::exceptions::InvalidIteration {static_cast<DataType>(data.index())};
        }
    }

    void Json::merge_patch(const Json & merge_patch) noexcept {
        apply_merge_patch(* this, merge_patch);
    }

    Json Json::merge(const Json & target) const {
        if (data.index() == DataType::array_type || data.index() == DataType::json_object_type) {
            if (data.index() != target.data.index()) {
                throw exceptions::InvalidMerge {static_cast<DataType>(target.data.index())};
            }
        } else if (target.data.index() == DataType::array_type || target.data.index() == DataType::json_object_type) {
            throw exceptions::InvalidMerge {};
        }
        Json new_json(static_cast<DataType>(data.index()));
        if (data.index() == DataType::array_type) {
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
        return std::get<DataType::integer_type>(data);
    }

    double & Json::get_double() {
        check_data(DataType::double_type);
        return std::get<DataType::double_type>(data);
    }

    bool & Json::get_bool() {
        check_data(DataType::boolean_type);
        return std::get<DataType::boolean_type>(data);
    }

    std::string & Json::get_string() {
        check_data(DataType::string_type);
        return * std::get<DataType::string_type>(data);
    }

    Array & Json::get_array() {
        check_data(DataType::array_type);
        return * std::get<DataType::array_type>(data);
    }

    JsonObject & Json::get_json_object() {
        check_data(DataType::json_object_type);
        return * std::get<DataType::json_object_type>(data);
    }

    void Json::update(const Json & target) {
        if (data.index() != DataType::json_object_type || target.data.index() != DataType::json_object_type) {
            throw exceptions::InvalidOperation {DataType::json_object_type};
        }
        for (const pair_type & item: target.items()) {
            JsonObject *&data_json_object {std::get<DataType::json_object_type>(data)};
            if (data_json_object->find(item.first) != data_json_object->cend()) {
                data_json_object->at(item.first) = item.second;
                continue;
            }
            data_json_object->insert(item);
        }
    }

    size_t Json::size() const noexcept {
        switch (data.index()) {
            case DataType::string_type:
            case DataType::integer_type:
            case DataType::boolean_type:
            case DataType::double_type:
                return 1;
            case DataType::array_type:
                return std::get<DataType::array_type>(data)->size();
            case DataType::json_object_type:
                return std::get<DataType::json_object_type>(data)->size();
            default:
                return 0;
        }
    }

    Json::iterator Json::find(const JsonKey & key) {
        return iterator {check_type<DataType::json_object_type>()->find(key)};
    }

    Json::iterator Json::find(const Json & item) {
        if (data.index() == DataType::array_type) {
            Array *&data_array {std::get<DataType::array_type>(data)};
            return iterator {std::find(data_array->begin(), data_array->end(), item)};
        } else if (data.index() == DataType::json_object_type) {
            JsonObject *&data_json_object {std::get<DataType::json_object_type>(data)};
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
        if (data.index() == DataType::array_type) {
            Array *const &data_array {std::get<DataType::array_type>(data)};
            return const_iterator {std::find(data_array->cbegin(), data_array->cend(), item)};
        } else {
            JsonObject *const &data_json_object {std::get<DataType::json_object_type>(data)};
            return const_iterator { std::find_if(
                    data_json_object->cbegin(),
                    data_json_object->cend(), [item](const pair_type & pair_item){
                        return pair_item.second == item;
                    }
            )};
        }
    }

    Json::const_iterator Json::find(const JsonKey & key) const {
        return const_iterator {check_type<DataType::json_object_type>()->find(key)};
    }

    Json::iterator Json::find_if(const std::function<bool(const Json &)> & test_func) {
        Array *&data_array {check_type<DataType::array_type>()};
        return iterator {std::find_if(data_array->begin(), data_array->end(), test_func)};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const Json &)> & test_func) const {
        Array *const &data_array {check_type<DataType::array_type>()};
        return const_iterator {
            std::find_if(data_array->cbegin(), data_array->cend(), test_func)};
    }

    Json::iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) {
        JsonObject * &data_json_object {check_type<DataType::json_object_type>()};
        return iterator {std::find_if(
                data_json_object->begin(), data_json_object->end(), test_func
                )};
    }

    Json::const_iterator Json::find_if(const std::function<bool(const pair_type &)> & test_func) const {
        JsonObject *const &data_json_object {check_type<DataType::json_object_type>()};
        return const_iterator {std::find_if(
                data_json_object->cbegin(), data_json_object->cend(), test_func
                )};
    }

    size_t Json::find_index(const Json & item) const {
        Array *const &data_array {check_type<DataType::array_type>()};
        return std::distance(
                data_array->cbegin(), std::find(data_array->cbegin(), data_array->cend(), item)
            );
    }

    size_t Json::find_index(const const_iterator & it) const {
        if (it.used_type != IteratorTypes::array_iterator_type) {
            throw iterators::exceptions::InvalidType{};
        }
        return std::distance(check_type<DataType::array_type>()->cbegin(), *it.array_iterator);
    }

    size_t Json::count(const Json & item) const {
        Array *const &data_array {check_type<DataType::array_type>()};
        return std::count(data_array->cbegin(), data_array->cend(), item);
    }

    bool Json::contains(const JsonKey & key) const {
        JsonObject *const &data_json_object {check_type<DataType::json_object_type>()};
        return data_json_object->find(key) != data_json_object->cend();
    }

    bool Json::contains(const Json & item) const {
        return find(item) != cend();
    }

    bool Json::empty() const {
        switch (data.index()) {
            case DataType::array_type:
                return std::get<DataType::array_type>(data)->empty();
            case DataType::json_object_type:
                return std::get<DataType::json_object_type>(data)->empty();
            default:
                throw exceptions::InvalidOperation {};
        }
    }

    Json & Json::at(const size_t index) const {
        return check_type<DataType::array_type>()->at(index);
    }

    Json & Json::at(const std::string & index) const {
        return check_type<DataType::json_object_type>()->at(JsonKey {index});
    }

    Json & Json::at(const JsonKey & key) const {
        return check_type<DataType::json_object_type>()->at(key);
    }

    Json & Json::at(const JsonPointer & json_pointer) const {
        can_iterate();
        const Json * tmp_return {this};
        for (const std::string & index: * json_pointer.pointer_list) {
            if (tmp_return->data.index() == DataType::array_type) {
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
        return check_type<DataType::json_object_type>()->get(key, default_return);
    }

    Json Json::get(const JsonKey & key, Json && default_return) const {
        return check_type<DataType::json_object_type>()->get(key, std::move(default_return));
    }

    Json Json::get(const std::string & key, const Json & default_return) const {
        return check_type<DataType::json_object_type>()->get(JsonKey {key}, default_return);
    }

    Json Json::get(const std::string & key, Json && default_return) const {
        return check_type<DataType::json_object_type>()->get(
                JsonKey {key}, std::move(default_return));
    }

    void Json::erase(long index) {
        Array *&data_array {check_type<DataType::array_type>()};
        data_array->erase(data_array->cbegin() + index);
    }

    void Json::erase(const std::string &index) {
        check_type<DataType::json_object_type>()->erase(JsonKey {index});
    }

    void Json::erase(const JsonKey &index) {
        check_type<DataType::json_object_type>()->erase(index);
    }

    void Json::erase(const JsonPointer &json_pointer) {
        Json & target {at(json_pointer.get_parent())};
        if (target.data.index() == DataType::array_type) {
            target.erase(static_cast<long>(json_pointer.get_index()));
        } else if (target.data.index() == DataType::json_object_type){
            std::get<DataType::json_object_type>(target.data)->erase(json_pointer.get_key());
        } else {
            throw exceptions::InvalidIndex {static_cast<DataType>(data.index())};
        }
    }

    void Json::push_back(const Json & new_item) {
        check_type<DataType::array_type>()->push_back(new_item);
    }

    void Json::insert(const pair_type & new_item) {
        check_type<DataType::json_object_type>()->insert(new_item);
    }

    void Json::insert(pair_type && new_item) {
        check_type<DataType::json_object_type>()->insert(std::move(new_item));
    }

    void Json::insert(const Json::const_iterator & position, const Json & item) {
        check_type<DataType::array_type>()->insert(* position.array_iterator, item);
    }

    void Json::insert(const Json::const_iterator & position, Json && item) {
        check_type<DataType::array_type>()->insert(* position.array_iterator, std::move(item));
    }

    Json::const_iterator Json::get_item(const long index) const {
        return const_iterator {check_type<DataType::array_type>()->cbegin() + index};
    }

    void Json::push_back(Json && new_item) {
        check_type<DataType::array_type>()->push_back(std::move(new_item));
    }

    Json & Json::back() const noexcept {
        return check_type<DataType::array_type>()->back();
    }

    JsonObject & Json::items() const {
        if (data.index() == DataType::json_object_type) {
            return *std::get<DataType::json_object_type>(data);
        }
        throw iterators::exceptions::InvalidType {};
    }

    #pragma endregion
}
