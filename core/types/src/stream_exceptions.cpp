#include "stream_exceptions.h"

const char * StreamInsertionException::what() const noexcept {
    return "Failed to insert the value into stream !";
}
