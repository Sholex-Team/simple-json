#include "indent.h"

using namespace simple_json;
using namespace ::indent;

size_t indent::indent_length = 0;

size_t indent::switch_indent(size_t new_indent) {
    size_t temp_indent = indent_length;
    indent_length = new_indent;
    return temp_indent;
}