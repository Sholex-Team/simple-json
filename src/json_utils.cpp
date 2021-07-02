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
        if (tmp_vector.back().empty()) {
            tmp_vector.erase(tmp_vector.end() - 1);
        }
        return tmp_vector;
    }

    bool is_digit(const std::string & str) {
        return std::all_of(str.begin(), str.end(), [](char ch) { return isdigit(ch); });
    }

    void replace_str(std::string & base, const std::string & old_value, const std::string & new_value) {
        std::string temp_str {};
        long difference {static_cast<long>(new_value.length()) - static_cast<long>(new_value.length())};
        for (long i {0}; i >= 0 && i < base.length(); ++i) {
            temp_str.push_back(base[i]);
            if (temp_str == old_value) {
                base.replace(i - old_value.length() + 1, old_value.length(), new_value);
                i += difference;
                temp_str.clear();
                continue;
            }
            if (old_value.rfind(temp_str, 0) == std::string::npos) {
                temp_str.clear();
            }
        }
    }

    void deserialize_json_pointer(std::string & base) {
        replace_str(base, "~1", "/");
        replace_str(base, "~0", "~");
    }

    void serialize_json_pointer(std::string & base) {
        replace_str(base, "~", "~0");
        replace_str(base, "/", "~1");
    }

    const char * json_type_to_string(const simple_json::types::DataType & type) {
        switch (type) {
            case types::DataType::integer_type: return "Integer";
            case types::DataType::string_type: return "String";
            case types::DataType::double_type: return "Double";
            case types::DataType::boolean_type: return "Boolean";
            case types::DataType::array_type: return "Array";
            case types::DataType::json_object_type: return "JsonObject";
            case types::DataType::null_type: return "Null";
            case types::DataType::string_key_type: return "JsonKey";
            case types::DataType::special_type: return "Special Type";
            case types::DataType::unknown: return "Unknown Type";
        }
    }
}
