#include "json_utils.h"

using namespace simple_json::utils {
    bool startswith(char * base, char * target) {
        for (size_t i; target[i] != '\0' || base[i] != '\0'; ++i) {
            if (target[i] != base[i]) {
                return false;
            }
        }
        return true;
    }
}
