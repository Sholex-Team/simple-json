#include "types/exceptions/bad_conversion.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    BadConversion::BadConversion(const DataType to) noexcept : JsonException(), to {to} {}

    #pragma endregion

    #pragma region Public Methods

    const char * BadConversion::what() const noexcept {
        switch (to) {
            case DataType::integer_type:
                return "Bad conversion to integer !";
            case DataType::double_type:
                return "Bad conversion to double !";
            case DataType::string_type:
                return "Bad conversion to std::string !";
            default:
                return "Bad Conversion !";
        }
    }

    #pragma endregion
}
