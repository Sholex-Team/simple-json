#include "base_exception.h"

BadConversion::BadConversion(DataType to) noexcept : std::exception(), to {to} {}

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