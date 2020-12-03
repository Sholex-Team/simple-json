#ifndef SIMPLE_JSON_BAD_CONVERSION_H
#define SIMPLE_JSON_BAD_CONVERSION_H
#include "base_exception.h"
class BadConversion : public BaseException {
private:
    DataType to;
public:
    const char * what() const noexcept override;
    BadConversion(DataType to) noexcept;
    BadConversion() noexcept : BaseException(), to {DataType::unknown} {}
};
#endif
