#ifndef SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
#define SIMPLE_JSON_ITERATOR_EXCEPTIONS_H

#include "base_exception.h"
#include "types/enum_types.h"

namespace simple_json::iterators::exceptions {
    class InvalidDereference : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };

    class InvalidIteration : public base_exceptions::JsonException {
    private:
        types::DataType used_type;
    public:
        explicit InvalidIteration(types::DataType used_type = types::DataType::unknown);
        const char * what() const noexcept override;
    };

    class InvalidType : public base_exceptions::JsonException {
    public:
        const char * what() const noexcept override;
    };

    class InvalidIterator : public base_exceptions::JsonException {
    private:
        types::IteratorTypes used_type;
    public:
        InvalidIterator(types::IteratorTypes used_type);
        const char * what() const noexcept override;
    };
}

#endif //SIMPLE_JSON_ITERATOR_EXCEPTIONS_H
