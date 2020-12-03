#ifndef SIMPLE_JSON_BASE_TYPE_H
#define SIMPLE_JSON_BASE_TYPE_H
#include <string>
class BaseItem {
private:
    union {
        unsigned int content_int;
        float content_float;
        std::string content_string;
    };
public:
    template<typename T>
    T get_data() {
    }
};
#endif
