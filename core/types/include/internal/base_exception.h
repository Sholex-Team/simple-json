#ifndef SIMPLE_JSON_BASE_EXCEPTION_H
#define SIMPLE_JSON_BASE_EXCEPTION_H
#include "enum_types.h"
#include <exception>
class BadConversion : public std::exception {
private:
    DataType to;
public:
    const char * what() const noexcept override;
    BadConversion(DataType to) noexcept;
    BadConversion() noexcept : std::exception(), to {DataType::unknown} {}
};
#endif
