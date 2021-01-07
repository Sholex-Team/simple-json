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

namespace simple_json::serializer {
    std::string dumps(const types::Json &, size_t = 0);
    void dump(types::Json &, const std::string &, size_t = 0);
    void dump(types::Json &, std::ofstream &, size_t = 0);

    namespace {
        class Dump {
        private:
            std::ofstream file_stream;
            size_t local_indent;
        public:
            // Constructor
            Dump(const std::string &, size_t);

            // Public Methods
            void dump(const types::Json &);

            // Destructors
            ~Dump();
        };

        void serializer(std::ostream &, const types::Json & json, size_t local_indent);
    }
}

#endif //SIMPLE_Json_SERIALIZER_H
