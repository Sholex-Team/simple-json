#ifndef SIMPLE_JSON_JSON_POINTER_H
#define SIMPLE_JSON_JSON_POINTER_H

#include <string>
#include <vector>
#include "json_utils.h"
#include "exceptions/invalid_pointer.h"
#include <cstdlib>

namespace simple_json::types {
    class Json;
    class JsonPatch;

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

        // Public Methods
        void add_to_path(std::string path);
        void add_to_path(size_t index);
        size_t get_index() const;

        // Operator Overloading
        bool operator==(const JsonPointer &) const;
        JsonPointer operator+(const std::string & r_path) const;
        JsonPointer operator+(size_t r_index) const;
        explicit operator std::string() const;

        // Friends
        friend std::ostream & operator<<(std::ostream &, const JsonPointer &);
        friend Json;
    };

    // Operator Overloading
    JsonPointer operator""_json_ptr(const char *, size_t);
    std::ostream & operator<<(std::ostream &, const JsonPointer &);
}

#endif //SIMPLE_JSON_JSON_POINTER_H
