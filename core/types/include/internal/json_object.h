#ifndef SIMPLE_JSON_JSON_OBJECT_H
#define SIMPLE_JSON_JSON_OBJECT_H
#include <map>
#include "base_type.h"
class JsonObject : public JsonItem, public std::map<std::string, JsonItem> {

};
#endif //SIMPLE_JSON_JSON_OBJECT_H
