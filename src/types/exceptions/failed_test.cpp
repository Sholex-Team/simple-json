#include "types/exceptions/failed_test.h"

namespace simple_json::types::exceptions {

    const char * FailedTest::what() const noexcept {
        return exception::what(); // TODO change text
    }
}