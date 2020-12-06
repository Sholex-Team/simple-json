#include "indent.h"

using namespace simple_json;
using namespace ::indent;

#pragma region Constructors

Indent::Indent(size_t indent_length) : indent_length {indent_length} {}

#pragma endregion

#pragma region Overloading OS

std::ostream & indent::operator<<(std::ostream & os, Indent & set_indent) {
    static_indent_obj = set_indent;
    return os;
}

std::ostream & indent::operator<<(std::ostream & os, Indent && set_indent) {
    os << set_indent;
    return os;
}

#pragma endregion
