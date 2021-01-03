#include "json_utils.h"
#include <algorithm>

namespace simple_json::utils {
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
