#include "base_exception.h"
#include <sstream>
#include <cstring>
#include <memory>

BadConversion::BadConversion(DataType from, DataType to) : std::exception(), from {from}, to {to} {}

const char * BadConversion::what() const noexcept {
    std::stringstream stream;
    stream << "Bad Conversion ";
    DataType unknown {100};
    if (from != unknown) {
        stream << "from ";
        stream << type_convertor(from) << " ";
    }
    if (to != unknown) {
        stream << "to ";
        stream << type_convertor(to) << " ";
    }
    stream << "!";
    std::shared_ptr message {std::make_shared<char [40]>()};
    size_t current {0};
    for(char c: stream.str()) {
        message[current] = c;
        ++current;
    }
    return message.get();
}