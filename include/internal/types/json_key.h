#ifndef SIMPLE_JSON_JSON_KEY_H
#define SIMPLE_JSON_JSON_KEY_H

#include <string>
#include <iostream>

namespace simple_json::types {
    class JsonObject;

    class JsonKey {
    private:
        std::string * key;
    public:
        // Constructors
        explicit JsonKey(const std::string & key);
        JsonKey(const JsonKey & json_key);
        JsonKey(JsonKey && json_key) noexcept;

        // Destructors
        ~JsonKey();

        // Operators
        bool operator<(const JsonKey & r_json_key) const;
        bool operator>(const JsonKey & r_json_key) const;
        bool operator==(const JsonKey & r_json_key) const;

        // Operator OStream
        friend std::ostream & operator<<(std::ostream & os, const JsonKey && json_key);
        friend std::ostream & operator<<(std::ostream & os, const JsonKey & json_key);
        friend JsonObject;

        // Public Methods
        inline const std::string & get_key() const {return * key;};
    };

    // Operator Overloading
    JsonKey operator""_json_key(const char * key_ptr, size_t);
    std::ostream & operator<<(std::ostream & os, const JsonKey && json_key);
    std::ostream & operator<<(std::ostream & os, const JsonKey & json_key);
}

#endif //SIMPLE_JSON_JSON_KEY_H
