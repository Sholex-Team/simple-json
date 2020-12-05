#include "stream_exceptions.h"

using namespace simple_json::types::exceptions;

#pragma region Public Methods

const char * StreamInsertionException::what() const noexcept {
    return "Failed to insert the value into stream !";
}

#pragma endregion
