#include "types/exceptions/deserializer_exceptions.h"

namespace simple_json::deserializer::exceptions {
    #pragma region Constructors

    ParsingException::ParsingException() : error {Errors::unknown} {}

    ParsingException::ParsingException(Errors error) : error {error} {}

    #pragma endregion

    #pragma region Public Methods

    const char * ParsingException::what() const noexcept {
        switch (error) {
            case Errors::illegal_array_split:
                return "Illegal \",\" used !";
            case Errors::illegal_key_split:
                return "Illegal use of \":\" !";
            case Errors::illegal_escape:
                return "Illegal use of \\ !";
            case Errors::empty_key:
                return "Json Key is empty !";
            case Errors::invalid_key:
                return "Json key is invalid !";
            case Errors::invalid_array:
                return "Invalid use of [ character !";
            case Errors::invalid_string:
                return "Invalid use of \" character !";
            case Errors::invalid_negative:
                return "Invalid use of character - !";
            default:
                return "String is not JSON serialized !";
        }
    }

    #pragma endregion
}
