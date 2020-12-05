#ifndef SIMPLE_JSON_JSON_KEY_H
#define SIMPLE_JSON_JSON_KEY_H

#include <string>

class JsonKey {
private:
    std::string * key;
public:
    // Constructors
    explicit JsonKey(char *);
    explicit JsonKey(std::string &);
    explicit JsonKey(std::string &&);
    JsonKey(JsonKey &);
    JsonKey(JsonKey &&) noexcept;

    // Destructors
    ~JsonKey();

    // Operators
    bool operator<(const JsonKey &);
    bool operator>(const JsonKey &);
    bool operator==(const JsonKey &);
};

// Operator Overloading
JsonKey operator""_json_key(const char *);

#endif //SIMPLE_JSON_JSON_KEY_H
