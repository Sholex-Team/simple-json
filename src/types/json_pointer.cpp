#include "json_pointer.h"
#include "json_utils.h"

namespace simple_json::type::json_pointer {
    #pragma region Constructors

    JsonPointer::JsonPointer(char * pointer_text) : pointer_text {new std::string {pointer_text}} {
        pointer_list = utils::split(pointer_text, "/");
    }
    JsonPointer::JsonPointer(std::string & pointer_text) : pointer_text {new std::string {pointer_text}} {
        pointer_list = utils::split(pointer_text, "/");
    }
    JsonPointer::JsonPointer(std::string && pointer_text) : JsonPointer(pointer_text) {}
    JsonPointer::JsonPointer(const JsonPointer & json_pointer) :
    pointer_text {new std::string {*json_pointer.pointer_text}}, pointer_list {json_pointer.pointer_list} {}
    JsonPointer::JsonPointer(JsonPointer && json_pointer) noexcept :
    pointer_text {json_pointer.pointer_text}, pointer_list {json_pointer.pointer_list} {
        json_pointer.pointer_text = nullptr;
    }

    #pragma endregion

    #pragma region Destructors

    JsonPointer::~JsonPointer() {
        delete pointer_text;
    }

    #pragma endregion

    #pragma region Oprator Overloading

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

    std::ostream & operator<<(std::ostream & os, const JsonPointer && json_pointer) {
        os << json_pointer;
        return os;
    }

    #pragma endregion

    #pragma region Public Method

    std::vector<std::string> JsonPointer::get_list_index() {
        return pointer_list;
    }

    #pragma endregion

}