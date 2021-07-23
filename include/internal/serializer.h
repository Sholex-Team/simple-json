#ifndef SIMPLE_Json_SERIALIZER_H
#define SIMPLE_Json_SERIALIZER_H

#include <string>
#include "types/json.h"
#include <sstream>
#include "indent.h"
#include <utility>
#include <fstream>
#include <iostream>
#include "types/exceptions/stream_exceptions.h"
#include "types/enum_types.h"

/*!
 * @brief Namespace dedicated to serialization
 *
 * This namespace contains functions and classes required for serialization operation which turns a Json object into a
 * JSON serialized string.
 */
namespace simple_json::serializer {
    /*!
     * @brief Serializes a Json object.
     *
     * This function serializes a Json object into a JSON string with intended indentation length.
     * @param json Json object which is going to get serialized.
     * @param local_indent Indentation length if needed.
     * @return Serialized JSON string
     */
    std::string dumps(const types::Json & json, size_t local_indent = 0);

    /*!
     * @brief Serializes a Json object.
     *
     * This function serializes a Json object and streams it into a file in given path with intended indentation.
     * @param json Json object which is going to get serialized.
     * @param file_path Destination file location.
     * @param local_indent Indentation length if needed.
     * @throw exceptions::WritingToFileException Throws if file path is invalid or writing operation fails for any
     * reason.
     */
    void dump(const types::Json & json, const std::string & file_path, size_t local_indent = 0);

    /*!
     * @brief Serializes a Json object.
     *
     * This function serializes a Json object and streams it into the given output file stream with intended
     * indentation.
     * @param json Json object which is going to get serialized.
     * @param file_stream File stream which is going to be used for storing the serialized JSON string.
     * @param local_indent Indentation length if needed.
     * @throw exceptions::WritingToFileException Throws if given output file stream is invalid or writing operation
     * fails for any reason.
     */
    void dump(const types::Json & json, std::ofstream & file_stream, size_t local_indent = 0);

    namespace {
        class Dump {
        private:
            std::ofstream file_stream;
            size_t local_indent;
        public:
            // Constructor
            Dump(const std::string & file_path, size_t local_indent);

            // Public Methods
            void dump(const types::Json & json);

            // Destructors
            ~Dump();
        };

        void serializer(std::ostream & os, const types::Json & json, size_t local_indent);
    }
}

/*! @example serializer.cpp
 * @brief Serializer usage example
 */

#endif //SIMPLE_Json_SERIALIZER_H
