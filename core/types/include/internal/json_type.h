
#ifndef SIMPLE_JSON_JSON_TYPE_H
#define SIMPLE_JSON_JSON_TYPE_H

#include <map>
#include <string>
#include "json_item.h"
#include "json_type.h"

typedef std::map<std::string, JsonItem> map_type;

class Json : public map_type {

};

#endif //SIMPLE_JSON_JSON_TYPE_H
