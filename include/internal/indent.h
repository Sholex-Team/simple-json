#ifndef SIMPLE_JSON_INDENT_H
#define SIMPLE_JSON_INDENT_H

#include <ostream>
#include "enum_types.h"

using simple_json::types::StreamType;

namespace simple_json::indent {
    struct Indent {
        static size_t indent_length;
    };

    inline StreamType set_indent(size_t length = 4)  {
        Indent::indent_length = length;
        return StreamType::indent;
    }

    inline StreamType unset_indent() {
        Indent::indent_length = 0;
        return StreamType::indent;
    }

    inline std::ostream & operator<<(std::ostream & os, StreamType &) {
        return os;
    }

    inline std::ostream & operator<<(std::ostream & os, StreamType &&) {
        return os;
    }
}

#endif //SIMPLE_JSON_INDENT_H
