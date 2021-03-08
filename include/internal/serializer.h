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
    std::string dumps(const types::Json & json, size_t local_indent = 0);
    void dump(const types::Json & json, const std::string & file_path, size_t local_indent = 0);
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

#endif //SIMPLE_Json_SERIALIZER_H
