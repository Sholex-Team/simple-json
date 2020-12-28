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
#include "stream_exceptions.h"

namespace simple_json::deserializer {
    types::Json loads(const std::string &);
    types::Json load(const std::string &);

    namespace {
        types::Json deserializer(std::istream &);

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
