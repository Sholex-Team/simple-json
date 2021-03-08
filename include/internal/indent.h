
#ifndef SIMPLE_JSON_INDENT_H
#define SIMPLE_JSON_INDENT_H

#include <ostream>

namespace simple_json::indent {
    struct SetIndent {};

    extern size_t indent_length;

    /** \example set_indent.cpp
         * This is an example of how to use the set_indent function.
    */
    inline SetIndent set_indent(size_t length = 2)  {
        indent_length = length;
        return {};
    }

    inline SetIndent unset_indent() {
        indent_length = 0;
        return {};
    }

    size_t switch_indent(size_t);

    inline std::ostream & operator<<(std::ostream & os, SetIndent &) {
        return os;
    }

    inline std::ostream & operator<<(std::ostream & os, SetIndent &&) {
        return os;
    }
}

#endif //SIMPLE_JSON_INDENT_H
