#include "stream_exceptions.h"

namespace simple_json {
    namespace serializer::exceptions {
    #pragma region Public Methods

        const char * StreamInsertionException::what() const noexcept {
            return "Failed to insert the value into stream !";
        }

        const char * WritingToFileException::what() const noexcept {
            return "Writing to file failed !";
        }

    #pragma endregion
    }

    namespace deserializer::exceptions {
    #pragma region Public Methods

        const char * ReadingFromFileException::what() const noexcept {
            return "Reading from file failed !";
        }

    #pragma endregion
    }
}
