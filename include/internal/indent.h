#ifndef SIMPLE_JSON_INDENT_H
#define SIMPLE_JSON_INDENT_H

#include <ostream>

namespace simple_json::indent {
    class Indent {
    private:
        size_t indent_length {0};
    public:
        Indent() = default;
        explicit Indent(size_t indent_length);
        [[nodiscard]] size_t get_indent_length() const { return indent_length; }
    } static static_indent_obj;

    inline Indent set_indent(size_t _indent_length = 4) {
        return Indent {_indent_length};
    }

    inline Indent unset_indent() {
        return Indent {};
    }

    std::ostream & operator<<(std::ostream &, Indent &);
    std::ostream & operator<<(std::ostream &, Indent &&);
}

#endif //SIMPLE_JSON_INDENT_H
