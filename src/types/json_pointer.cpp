#include "types/json_pointer.h"
#include <iostream>

namespace simple_json::types {
    #pragma region Constructors

    JsonPointer::JsonPointer(std::string & pointer_text) : pointer_text {new std::string {pointer_text}},
    pointer_list {new std::vector<std::string> {utils::split(pointer_text, "/")}} {
        if (!pointer_list->begin()->empty()) {
            throw exceptions::InvalidPointer {};
        }
        pointer_list->erase(pointer_list->begin());
        for (std::string & pointer_item: * pointer_list) {
            utils::deserialize_json_pointer(pointer_item);
        }
    }

    JsonPointer::JsonPointer(std::string && pointer_text) : JsonPointer(pointer_text) {}

    JsonPointer::JsonPointer(const JsonPointer & json_pointer) :
    pointer_text {new std::string {* json_pointer.pointer_text}},
    pointer_list {new std::vector<std::string> {* json_pointer.pointer_list}} {}

    JsonPointer::JsonPointer(JsonPointer && json_pointer) noexcept :
    pointer_text {json_pointer.pointer_text}, pointer_list {json_pointer.pointer_list} {
        json_pointer.pointer_text = nullptr;
        json_pointer.pointer_list = nullptr;
    }

    #pragma endregion

    #pragma region Destructor

    JsonPointer::~JsonPointer() {
        delete pointer_text;
        delete pointer_list;
    }

    #pragma endregion

    #pragma region Operator Overloading

    bool JsonPointer::operator==(const JsonPointer & json_pointer) const {
        return pointer_text == json_pointer.pointer_text;
    }

    JsonPointer operator""_json_ptr(const char * pointer_ptr, size_t) {
        return JsonPointer {pointer_ptr};
    }

    std::ostream & operator<<(std::ostream & os, const JsonPointer & json_pointer) {
        os << * json_pointer.pointer_text;
        return os;
    }

    JsonPointer::operator std::string() const {
        return * pointer_text;
    }

    JsonPointer JsonPointer::operator+(const std::string & r_path) const {
        std::string new_pointer {* pointer_text};
        return JsonPointer {(new_pointer.back() == '/') ?
        new_pointer.append(r_path) : (new_pointer + '/').append(r_path)};
    }

    JsonPointer JsonPointer::operator+(const JsonKey & r_path) const {
        std::string new_pointer {* pointer_text};
        std::string serialized_key {r_path.get_key()};
        utils::serialize_json_pointer(serialized_key);
        return JsonPointer {(new_pointer.back() == '/') ?
        new_pointer.append(serialized_key) : (new_pointer + '/').append(serialized_key)};
    }

    JsonPointer  JsonPointer::operator+(const size_t r_index) const {
        return * this + std::to_string(r_index);
    }

    #pragma endregion

    #pragma region Public Methods

    void JsonPointer::add_to_path(std::string path) {
        pointer_text->push_back('/');
        pointer_text->append(path);
        utils::deserialize_json_pointer(path);
        pointer_list->push_back(path);
    }

    void JsonPointer::add_to_path(const size_t index) {
        pointer_list->push_back(std::to_string(index));
        pointer_text->push_back('/');
        pointer_text->append(std::to_string(index));
    }

    size_t JsonPointer::get_index() const {
        check_pointer(DataType::array_type);
        return std::strtoul(pointer_list->back().c_str(), nullptr, 10);
    }

    JsonKey JsonPointer::get_key() const {
        check_pointer(DataType::json_object_type);
        return JsonKey {pointer_list->back()};
    }

    JsonPointer JsonPointer::get_parent() const {
        if (pointer_list->empty()) {
            throw exceptions::InvalidPointer {};
        }
        std::string tmp {* pointer_text};
        std::string last_pointer {pointer_list->back()};
        utils::serialize_json_pointer(last_pointer);
        tmp = tmp.substr(0, tmp.length() - (last_pointer.length() + 1));
        if (tmp.empty()) {
            tmp.push_back('/');
        }
        return JsonPointer {tmp};
    }

    bool JsonPointer::check_ended() const {
        return pointer_list->back() == "-";
    }

    #pragma endregion

    #pragma region Private Methods

    void JsonPointer::check_pointer(DataType used_type) const {
        if (pointer_list->empty()) {
            throw exceptions::InvalidPointer {};
        }
        bool is_digit {utils::is_digit(pointer_list->back())};
        if (used_type == DataType::array_type) {
            if (!is_digit) {
                throw exceptions::InvalidPointer {};
            }
            return;
        }
        if (is_digit) {
            throw exceptions::InvalidPointer {};
        }
    }

    #pragma endregion
}