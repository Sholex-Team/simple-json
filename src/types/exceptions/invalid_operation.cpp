#include "types/exceptions/invalid_operation.h"

namespace simple_json::types::exceptions {
    #pragma region Constructors

    InvalidOperation::InvalidOperation(const DataType used_type, const DataType operation_type) :
    base_exceptions::JsonErrorTextException {} {
        error_text->append("Invalid ");
        error_text->append(utils::json_type_to_string(operation_type));
        error_text->append(" operation attempt on ");
        error_text->append(utils::json_type_to_string(used_type));
        error_text->append(" !");
    }

    #pragma endregion
}
