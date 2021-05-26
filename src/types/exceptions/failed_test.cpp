#include "types/exceptions/failed_test.h"

namespace simple_json::types::exceptions {
    #pragma region Consturctors

    FailedTest::FailedTest(const JsonPointer & json_pointer, Error error) {
        if (error == Error::INVALID_VALUE) {
            error_text = "Test failed at ";
        } else {
            error_text = "Path does not exist : ";
        }
        error_text.append(static_cast<std::string>(json_pointer));
    }

    #pragma endregion

    #pragma region Public Methods

    const char * FailedTest::what() const noexcept {
        return error_text.c_str();
    }

    #pragma endregion
}
