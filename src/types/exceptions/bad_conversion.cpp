#include "types/exceptions/bad_conversion.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    BadConversion::BadConversion(const DataType src, const DataType dst) noexcept : JsonException(),
            error_text {new std::string {"Invalid conversion attempt from "}} {
        error_text->append(utils::json_type_to_string(src));
        error_text->append(" type to ");
        error_text->append(utils::json_type_to_string(dst));
        error_text->append(" type !");
    }

    #pragma endregion

    #pragma region Public Methods

    const char * BadConversion::what() const noexcept {
        return error_text->c_str();
    }

    #pragma endregion

    #pragma region Destructor

    BadConversion::~BadConversion() {
        delete error_text;
    }

    #pragma endregion
}
