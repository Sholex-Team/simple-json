#ifndef SIMPLE_JSON_JSON_POINTER_H
#define SIMPLE_JSON_JSON_POINTER_H

#include <string>
#include <vector>

namespace simple_json::types {
    class JsonPointer {
    private:
        std::string * pointer_text;
        std::vector<std::string> * pointer_list;
    public:
        // Constructors
        explicit JsonPointer(std::string &);
        explicit JsonPointer(std::string &&);
        JsonPointer(const JsonPointer &);
        JsonPointer(JsonPointer &&) noexcept;

        // Destructors
        ~JsonPointer();

        // Operator Overloading
        bool operator==(const JsonPointer &) const;
        friend std::ostream & operator<<(std::ostream &, const JsonPointer &);

        // Public Method
        inline std::vector<std::string> get_list_index() {
            return * pointer_list;
        }
    };

    // Operator Overloading
    JsonPointer operator""_json_ptr(const char *, size_t);
    std::ostream & operator<<(std::ostream &, const JsonPointer &)
}

#endif //SIMPLE_JSON_JSON_POINTER_H
