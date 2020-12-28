#include "json_utils.h"

namespace simple_json::utils {
    bool startswith(char *base, char *target) {
        for (size_t i{0}; target[i] != '\0' || base[i] != '\0'; ++i) {
            if (target[i] != base[i]) {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> split(std::string base, std::string target) {
        std::vector<std::string> tmp_vector;
        size_t first_index {0};
        for (size_t i{0}; i < base.length(); ++i) {
            if (base[i] == target[0]) {
                bool is_split {true};
                size_t base_index{i + 1};
                for (
                        size_t target_index{1};
                        target_index < target.length(); ++target_index, ++base_index
                ) {
                    if (base[base_index] != target[target_index] || base_index >= base.length()) {
                        is_split = false;
                        break;
                    }
                }
                if (is_split) {
                    tmp_vector.push_back(base.substr(first_index, i - first_index));
                    first_index = base_index;
                    i = first_index - 1;
                } else {
                    continue;
                }
            }
        }
        tmp_vector.push_back(base.substr(first_index, base.length() - 1));
        return tmp_vector;
    }
}
