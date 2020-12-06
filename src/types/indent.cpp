#include "indent.h"

#pragma region Overloading OS

std::ostream & operator<<(std::ostream & os, Indent & set_indent) {
    static_indent_obj = set_indent;
    return os;
}

#pragma endregion
