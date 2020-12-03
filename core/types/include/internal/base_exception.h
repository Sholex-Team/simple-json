#ifndef SIMPLE_JSON_BASE_EXCEPTION_H
#define SIMPLE_JSON_BASE_EXCEPTION_H
#include "enum_types.h"
#include <exception>
class BadConversion : public std::exception {
private:
    DataType from;
    DataType to;
public:
    const char * what() const noexcept override;
    BadConversion(DataType from, DataType to);
    BadConversion() : std::exception(), from {100}, to {100} {};
};
#endif
