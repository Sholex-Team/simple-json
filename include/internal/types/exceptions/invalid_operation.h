#ifndef SIMPLE_JSON_INVALID_OPERATION_H
#define SIMPLE_JSON_INVALID_OPERATION_H

#include "base_exception.h"
#include "../enum_types.h"

namespace simple_json::types::exceptions {
    class InvalidOperation : public base_exceptions::JsonException {
    private:
        DataType used_type;
    public:
        // Constructors
        explicit InvalidOperation(DataType used_type = DataType::unknown);

        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_INVALID_OPERATION_H
