#ifndef SIMPLE_JSON_JSON_UTILS_H
#define SIMPLE_JSON_JSON_UTILS_H


#include <vector>
#include <string>

namespace simple_json::utils {
    std::vector<std::string> split(std::string, const std::string &);
    bool is_digit(const std::string &);
}

#endif //SIMPLE_JSON_JSON_UTILS_H
