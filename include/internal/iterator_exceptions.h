#ifndef SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
#define SIMPLE_JSON_ITERATOR_EXCEPTIONS_H

#include "base_exception.h"
#include "enum_types.h"

namespace simple_json::iterators::exceptions {
    class InvalidDereference : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };

    class InvalidIteration : public base_exceptions::JsonException {
    private:
        types::DataType from;
    public:
        InvalidIteration();
        explicit InvalidIteration(types::DataType);
        const char * what() const noexcept override;
    };

    class InvalidType : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
