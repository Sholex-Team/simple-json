#ifndef SIMPLE_JSON_INVALID_PATCH_OPERATION_H
#define SIMPLE_JSON_INVALID_PATCH_OPERATION_H

#include <string>
#include "base_exception.h"

namespace simple_json::types::exceptions {
    class InvalidPatchOperation : public base_exceptions::JsonException {
    private:
        std::string operation;
    public:
        // Constructors
        explicit InvalidPatchOperation(const std::string operation);

        // Public Methods
        const char * what() const noexcept override;
    };
}

#endif
