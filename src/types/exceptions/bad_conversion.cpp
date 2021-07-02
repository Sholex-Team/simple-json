#include "types/exceptions/bad_conversion.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    BadConversion::BadConversion(const DataType src, const DataType dst) noexcept :
    base_exceptions::JsonErrorTextException {} {
        error_text->append("Invalid conversion attempt from ");
        error_text->append(utils::json_type_to_string(src));
        error_text->append(" type to ");
        error_text->append(utils::json_type_to_string(dst));
        error_text->append(" type !");
    }

    #pragma endregion
}
