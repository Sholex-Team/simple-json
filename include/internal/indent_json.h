
#ifndef SIMPLE_JSON_INDENT_JSON_H
#define SIMPLE_JSON_INDENT_JSON_H

#include <ostream>

class _Indent {
private:
    size_t indent_length {0};
public:
    _Indent() = default;
    explicit _Indent(size_t indent_length) : indent_length(indent_length) {}
    [[nodiscard]] size_t get_indent_length() const { return indent_length; }
} static static_indent_obj;

_Indent set_indent(size_t _indent_length = 4) {
    return _Indent {_indent_length};
}

_Indent unset_indent() {
    return _Indent();
}

std::ostream & operator<<(std::ostream & os, _Indent & set_indent) {
    static_indent_obj = set_indent;
    return os;
}

#endif //SIMPLE_JSON_INDENT_JSON_H
