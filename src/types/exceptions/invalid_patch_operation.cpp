#include "types/exceptions/invalid_patch_operation.h"

namespace simple_json::types::exceptions {
    #pragma region Public Methods

    const char * simple_json::types::exceptions::InvalidPatchOperation::what() const noexcept {
        return "Operation used invalid !";
    }

    #pragma endregion
}
