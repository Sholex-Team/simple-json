#ifndef SIMPLE_JSON_JSON_UTILS_H
#define SIMPLE_JSON_JSON_UTILS_H


#include <vector>
#include <string>

namespace simple_json::utils {
    bool startswith(const char *, const char *);
    std::vector<std::string> split(std::string, const std::string &);
}

#endif //SIMPLE_JSON_JSON_UTILS_H
