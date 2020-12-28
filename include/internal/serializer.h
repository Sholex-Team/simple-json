#ifndef SIMPLE_Json_SERIALIZER_H
#define SIMPLE_Json_SERIALIZER_H

#include <string>
#include "json.h"
#include <sstream>
#include "indent.h"
#include <utility>
#include <fstream>
#include "stream_exceptions.h"

namespace simple_json::serializer {
    std::string dumps(const types::Json &, size_t = 0);
    void dump(types::Json &, const std::string &, size_t = 0);
    void dump(types::Json &, std::ofstream &, size_t = 0);

    namespace {
        class Dump {
        private:
            std::ofstream file_stream;
        public:
            // Constructor
            Dump(const types::Json &, const std::string &, size_t);

            ~Dump();
        };
    }
}

#endif //SIMPLE_Json_SERIALIZER_H
