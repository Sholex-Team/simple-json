#include "simple_json.h"
#include "string"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace deserializer;

int main() {
    std::string test_json {R"(
  {
    "nameHash": "WEAPON_NAVYREVOLVER",
    "hash": -1853920116,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_wep2_gun",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_REV_NV",
    "gxtDescription": "WTD_REV_NV",
    "components": [
      {
        "nameHash": "COMPONENT_NAVYREVOLVER_CLIP_01",
        "hash": -1738620313,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  })"};
    Json loaded(loads(test_json));
    std::cout << loaded << std::endl;
    return 0;
}
