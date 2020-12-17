#include "deserializer_exceptions.h"

namespace simple_json::deserializer::exceptions {
    const char * ParsingException::what() const noexcept {
        return "String is not JSON serialized !";
    }
}
