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

namespace simple_json::deserializer {
    types::Json loads(const std::string &);
    types::Json load(const std::string &);
    types::Json load(std::ifstream &);

    namespace {
        class Deserializer {
        private:
            // Properties
            types::Json main_object {types::DataType::unknown};
            std::stack<types::Json *> primary_stack {};
            std::string last_value {};
            std::string last_key {};
            types::DataType last_type {types::DataType::unknown};
            bool escaped {false};
            bool finished {false};
            bool key_split {false};
            bool array_split {false};
            char false_str [6] {"false"};
            char true_str [5] {"true"};
            char null_str [5] {"null"};
            char ch;
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
        public:
            types::Json deserialize(std::istream &);
            types::Json deserialize(std::istream &&);
        };

        class Load {
        private:
            std::ifstream file_stream;
        public:
            types::Json load();
            explicit Load(const std::string &);
            ~Load();
        };
    }
}

#endif //SIMPLE_JSON_DESERIALIZER_H
