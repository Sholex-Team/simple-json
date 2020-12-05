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
    bool operator<(const JsonKey &) const;
    bool operator>(const JsonKey &) const;
    bool operator==(const JsonKey &) const;
};

// Operator Overloading
JsonKey operator""_json_key(const char *, size_t);

#endif //SIMPLE_JSON_JSON_KEY_H
