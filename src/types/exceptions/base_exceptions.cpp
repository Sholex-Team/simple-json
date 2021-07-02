#include "types/exceptions/base_exceptions.h"

namespace simple_json::base_exceptions {
    #pragma region Public Methods

    const char * JsonErrorTextException::what() const noexcept {
        return error_text->c_str();
    }

    #pragma endregion

    #pragma region Destructor

    JsonErrorTextException::~JsonErrorTextException() {
        delete error_text;
    }

    #pragma endregion
}
