#include "types/exceptions/failed_test.h"

namespace simple_json::types::exceptions {
    #pragma region Public Methods

    const char * FailedTest::what() const noexcept {
        return "JSON Patch test failed !";
    }

    #pragma endregion
}
