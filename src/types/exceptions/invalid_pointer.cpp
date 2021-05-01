#include "types/exceptions/invalid_pointer.h"

namespace simple_json::types::exceptions {
    #pragma region Public Methods

    const char * InvalidPointer::what() const noexcept {
        return "JSON pointer is not valid !";
    }

    #pragma endregion
}
