#ifndef SIMPLE_JSON_SERIALIZER_H
#define SIMPLE_JSON_SERIALIZER_H

#include <string>
#include "json.h"
#include <sstream>
#include "indent.h"
#include <utility>
#include <fstream>
#include "stream_exceptions.h"

using namespace simple_json::types;

namespace simple_json::serializer {
    std::string dumps(const Json &, size_t = 0);

    class Dump {
    private:
        std::ofstream file_stream;
    public:
        // Constructor
        Dump(const Json &, const std::string &, size_t);
        ~Dump();
    };

    void dump(Json &, const std::string &, size_t = 0);
}

#endif //SIMPLE_JSON_SERIALIZER_H
