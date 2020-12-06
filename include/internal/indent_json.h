
#ifndef SIMPLE_JSON_INDENT_JSON_H
#define SIMPLE_JSON_INDENT_JSON_H

#include <ostream>

enum indent_enum {
    set_indent_enum,
    unset_indent_enum
};

struct IndentState {
    indent_enum indent {indent_enum::unset_indent_enum};
    int indent_sze {0};
};

static IndentState current_state;

inline std::ostream & set_indent(std::ostream & os) {
    current_state.indent = indent_enum::set_indent_enum;
    current_state.indent_sze = 4;
    return os;
}

inline std::ostream & unset_indent(std::ostream & os) {
    current_state.indent = indent_enum::unset_indent_enum;
    return os;
}

#endif //SIMPLE_JSON_INDENT_JSON_H
