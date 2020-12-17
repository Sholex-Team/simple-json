#include "base_exception.h"

#ifndef SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
#define SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
namespace simple_json::deserializer::exceptions {
    class ParsingException : public simple_json::base_exceptions::JsonException {
    public:
        // Public Methods
        const char * what() const noexcept override;
    };
}
#endif //SIMPLE_JSON_DESERIALIZER_EXCEPTIONS_H
