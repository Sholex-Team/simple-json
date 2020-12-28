#ifndef SIMPLE_JSON_DESERIALIZER_H
#define SIMPLE_JSON_DESERIALIZER_H

#include "json.h"
#include <fstream>
#include <string>
#include <stack>
#include <utility>
#include "enum_types.h"
#include "deserializer_exceptions.h"
#include <cstdlib>
#include <iostream>

namespace simple_json::deserializer {
    simple_json::types::Json loads(const std::string &);
    simple_json::types::Json load(std::string);

    namespace {
        simple_json::types::Json deserializer(std::istream &);

        class Load {
        private:
            std::ifstream file_stream;
        public:
            simple_json::types::Json load();
            explicit Load(std::string);
            ~Load();
        };
    }
}

#endif //SIMPLE_JSON_DESERIALIZER_H
