#include "indent.h"

namespace simple_json::indent {
    size_t indent_length = 0;

    size_t switch_indent(size_t new_indent) {
        size_t temp_indent = indent_length;
        indent_length = new_indent;
        return temp_indent;
    }
}
