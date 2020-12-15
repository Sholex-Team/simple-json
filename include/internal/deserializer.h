
#ifndef SIMPLE_JSON_DESERIALIZER_H
#define SIMPLE_JSON_DESERIALIZER_H

#include "json.h"
#include <fstream>

namespace simple_json::deserializer {
    simple_json::types::Json loads(const std::string &);

    class Load {
    private:
        std::ifstream file_stream;
    public:
        Load(std::string);
        ~Load();
    };

    simple_json::types::Json load(std::string);
}

#endif //SIMPLE_JSON_DESERIALIZER_H
