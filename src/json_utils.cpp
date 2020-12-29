#include "json_utils.h"
#include <algorithm>

namespace simple_json::utils {
    bool startswith(const char *base, const char *target) {
        for (size_t i{0}; target[i] != '\0' || base[i] != '\0'; ++i) {
            if (target[i] != base[i]) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> split(std::string base, const std::string & target) {
        std::vector<std::string> tmp_vector;
        size_t index;
        while ((index = base.find(target)) != std::string::npos) {
            tmp_vector.push_back(base.substr(0, index));
            base = base.substr(index + target.length(), base.length() - index - target.length());
        }
        tmp_vector.push_back(base);
        return tmp_vector;
    }

    bool is_digit(const std::string & str) {
        return std::all_of(str.begin(), str.end(), [](char ch) { return isdigit(ch); });
    }
}
