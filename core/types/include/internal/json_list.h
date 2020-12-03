#ifndef SIMPLE_JSON_JSON_LIST_H
#define SIMPLE_JSON_JSON_LIST_H
#include "base_type.h"
#include <vector>
class JsonList : public JsonItem, public std::vector<JsonItem> {

};
#endif //SIMPLE_JSON_JSON_LIST_H
