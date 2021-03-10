#ifndef SIMPLE_JSON_STREAM_EXCEPTIONS_H
#define SIMPLE_JSON_STREAM_EXCEPTIONS_H

#include "base_exception.h"
#include "../array_type.h"

namespace simple_json {
    namespace serializer::exceptions {
        /*!
         * @brief Stream Insertion exception.
         *
         * This exception throws when serializer fail to write into a output stream.
         */
        class StreamInsertionException : public simple_json::base_exceptions::JsonException {
        public:
            const char * what() const noexcept override;
        };

        /*!
         * @brief Writing To File exception.
         *
         * This exception throws when serializer fail to write into a file or the file is not open for any reason.
         */
        class WritingToFileException : public simple_json::base_exceptions::JsonException {
        public:
            const char * what() const noexcept override;
        };
    }
    /*! @namespace simple_json::serializer::exceptions
     * @brief A namespace dedicated to serializer exceptions.
     *
     * This namespace contains all the exceptions related to serializer and serializing operations.
     */

    namespace deserializer::exceptions {
        class ReadingFromFileException : public simple_json::base_exceptions::JsonException {
        public:
            const char * what() const noexcept override;
        };
    }
    /*! @namespace deserializer::exceptions
     * @brief A namespace dedicated to deserializer exceptions.
     *
     * This namespace contains all the exceptions related to deserializer and deserializing operations.
     */
}

#endif //SIMPLE_JSON_STREAM_EXCEPTIONS_H
