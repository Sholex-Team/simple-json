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

    #pragma endregion

    #pragma region Public Methods

    void JsonPointer::add_to_path(std::string path) {
        utils::replace_str(path, "~1", "/");
        utils::replace_str(path, "~0", "~");
        pointer_list->push_back(path);
    }

    #pragma endregion
}