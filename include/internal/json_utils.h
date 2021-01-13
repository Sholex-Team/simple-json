#ifndef SIMPLE_JSON_JSON_UTILS_H
#define SIMPLE_JSON_JSON_UTILS_H


#include <vector>
#include <string>

namespace simple_json::utils {
    std::vector<std::string> split(std::string base, const std::string & target);
    bool is_digit(const std::string & str);
    void replace_str(std::string & base, const std::string & old_value, const std::string & new_value);
}

#endif //SIMPLE_JSON_JSON_UTILS_H
