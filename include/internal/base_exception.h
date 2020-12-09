#ifndef SIMPLE_JSON_BASE_EXCEPTION_H
#define SIMPLE_JSON_BASE_EXCEPTION_H

#include <exception>

namespace simple_json::base_exceptions {
    class JsonException : public std::exception {};
}

#endif //SIMPLE_JSON_BASE_EXCEPTION_H
