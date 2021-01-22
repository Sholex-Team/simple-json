#include "types/json_pointer.h"

namespace simple_json::types {
    #pragma region Constructors

    JsonPointer::JsonPointer(std::string & pointer_text) : pointer_text {new std::string {pointer_text}},
    pointer_list {new std::vector<std::string> {utils::split(pointer_text, "/")}} {
        if (!pointer_list->begin()->empty()) {
            throw exceptions::InvalidPointer {};
        }
        pointer_list->erase(pointer_list->begin());
        for (std::string & pointer_item: * pointer_list) {
            utils::replace_str(pointer_item, "~1", "/");
            utils::replace_str(pointer_item, "~0", "~");
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

    JsonPointer operator""_json_ptr(const char * pointer_text, size_t) {
        return JsonPointer {pointer_text};
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

    JsonPointer  JsonPointer::operator+(const size_t r_index) const {
        return * this + std::to_string(r_index);
    }

    #pragma endregion

    #pragma region Public Methods

    void JsonPointer::add_to_path(std::string path) {
        utils::replace_str(path, "~1", "/");
        utils::replace_str(path, "~0", "~");
        pointer_list->push_back(path);
        pointer_text->push_back('/');
        pointer_text->append(path);
    }

    void JsonPointer::add_to_path(const size_t index) {
        pointer_list->push_back(std::to_string(index));
        pointer_text->push_back('/');
        pointer_text->append(std::to_string(index));
    }

    size_t JsonPointer::get_index() const {
        check_pointer(array_type);
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
        utils::replace_str(tmp, '/' + pointer_list->back(), "");
        if (tmp.empty()) {
            tmp.push_back('/');
        }
        return JsonPointer {tmp};
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