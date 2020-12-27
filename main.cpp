#include "simple_json.h"
#include "string"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    std::string test_json {R"([{
    "nameHash": "VEHICLE_WEAPON_RUINER_BULLET",
    "hash": 50118905,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RUINER_ROCKET",
    "hash": 84788907,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_PLANEMSL",
    "gxtDescription": "WTD_V_PLANEMSL",
    "components": []
  }])"};
    Json loaded(loads(test_json));
    std::cout << loaded << std::endl;
    return 0;
}
