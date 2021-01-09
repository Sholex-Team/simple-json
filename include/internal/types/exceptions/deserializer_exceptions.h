#include "base_exception.h"
#include <cinttypes>

#ifndef SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
#define SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
namespace simple_json::deserializer::exceptions {
    class ParsingException : public simple_json::base_exceptions::JsonException {
    public:
        // Errors
        enum Errors : std::uint8_t {
            illegal_array_split,
            illegal_key_split,
            illegal_escape,
            empty_key,
            invalid_key,
            invalid_array,
            invalid_string,
            illegal_space,
            invalid_character,
            extra_character,
            illegal_escape_sequences,
            unfinished_json,
            unknown
        };

        // Constructors
        ParsingException();
        ParsingException(Errors);

        // Public Methods
        const char * what() const noexcept override;
    private:
        Errors error;
    };
}
#endif //SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
