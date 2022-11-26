#ifndef SIMPLE_JSON_DESERIALIZER_H
#define SIMPLE_JSON_DESERIALIZER_H

#include "types/json.h"
#include <fstream>
#include <string>
#include <stack>
#include <utility>
#include "types/enum_types.h"
#include "types/exceptions/deserializer_exceptions.h"
#include <cstdlib>
#include <iostream>
#include "types/exceptions/stream_exceptions.h"
#include "json_utils.h"
#include <sstream>

/*!
 * @brief Namespace dedicated to deserialization
 *
 * This namespace contains functions and classes required for deserializing a JSON string and turning it into a Json
 * type object.
 */
namespace simple_json::deserializer {
    /*!
     * @brief Deserializes a string.
     *
     * This function gets a string as input and deserializes it into a Json type object.
     * @param json_text Serialized JSON std::string
     * @return Deserialized Json object
     * @throw exceptions::ParsingException Throws this exception when there is a problem in JSON string serialization.
     */
    [[nodiscard]] types::Json loads(const std::string & json_text);

    /*!
     * @brief Deserializes a serialized JSON file.
     *
     * This function gets a file path as input, reads the file and deserializes it.
     * @param file_path Json serialized file path
     * @throw exceptions::ReadingFromFileException Throws this exception when it fails to read the file from the
     * given path.
     * @throw exceptions::ParsingException Throws this exception when there is a problem in JSON string serialization.
     * @return Deserialized Json object created from serialized Json file
     */
    [[nodiscard]] types::Json load(const std::string & file_path);

    /*!
     * @brief Deserializes a serialized JSON file.
     *
     * This functions gets a file input stream, reads the file from it and deserializes it.
     * @param fs Input file stream.
     * @throw exceptions::ReadingFromFileException Throws this exception when it fails to read from input file stream.
     * @throw exceptions::ParsingException Throws this exception when there is a problem in JSON string serialization.
     * @return Deserialized Json object based on given input file stream
     */
    [[nodiscard]] types::Json load(std::ifstream & fs);

    namespace {
        class Deserializer {
        private:
            // Properties
            types::Json main_object;
            std::stack<types::Json *> primary_stack {};
            std::string last_value {};
            std::string last_key {};
            types::DataType last_type {types::DataType::unknown};
            bool escaped {false};
            bool finished {false};
            bool key_split {false};
            bool array_split {false};
            bool is_spaced {false};
            std::string false_str {"false"};
            std::string true_str {"true"};
            std::string null_str {"null"};
            char ch {};
            long int integer_value {};
            double double_value {};

            // Private Methods
            void add_to_top();
            void pop_stack();
            void strings_or_exception();
            void string_push_or_exception();
            void push_json_object_stack();
            void push_array_stack();
            void set_main_object();
            bool is_special();
            void general_push_or_exception();
        public:
            Deserializer(): main_object (types::DataType::unknown) {};

            [[nodiscard]] types::Json deserialize(std::istream & steam);
            [[nodiscard]] types::Json deserialize(std::istream && stream);
        };

        class Load {
        private:
            std::ifstream file_stream;
        public:
            [[nodiscard]] types::Json load();
            [[nodiscard]] explicit Load(const std::string & file_path);
            ~Load();
        };
    }
}

/*! @example deserializer.cpp
 * @brief Deserializer usage example.
 */

#endif //SIMPLE_JSON_DESERIALIZER_H
