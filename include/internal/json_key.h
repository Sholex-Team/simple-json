#ifndef SIMPLE_JSON_JSON_KEY_H
#define SIMPLE_JSON_JSON_KEY_H

#include <string>
#include <iostream>

namespace simple_json::types {
    class JsonKey {
    private:
        std::string * key;
    public:
        // Constructors
        explicit JsonKey(char *);
        explicit JsonKey(std::string &);
        explicit JsonKey(std::string &&);
        JsonKey(const JsonKey &);
        JsonKey(JsonKey &&) noexcept;

        // Destructors
        ~JsonKey();

        // Operators
        bool operator<(const JsonKey &) const;
        bool operator>(const JsonKey &) const;
        bool operator==(const JsonKey &) const;

        // Operator OStream
        friend std::ostream & operator<<(std::ostream &, const JsonKey &&);
        friend std::ostream & operator<<(std::ostream &, const JsonKey &);
    };

    // Operator Overloading
    JsonKey operator""_json_key(const char *, size_t);
    std::ostream & operator<<(std::ostream &, const JsonKey &&);
    std::ostream & operator<<(std::ostream &, const JsonKey &);
}

#endif //SIMPLE_JSON_JSON_KEY_H
