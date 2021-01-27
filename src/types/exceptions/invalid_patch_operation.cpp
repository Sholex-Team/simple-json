#include "types/exceptions/invalid_patch_operation.h"
#include <utility>

simple_json::types::exceptions::InvalidPatchOperation::InvalidPatchOperation(std::string operation) :
        operation{std::move(operation)} {}

const char * simple_json::types::exceptions::InvalidPatchOperation::what() const noexcept {
    return "Operation used invalid !";
}
