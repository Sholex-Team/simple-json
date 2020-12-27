#include "simple_json.h"
#include "string"
#include <iostream>

using namespace simple_json;
using namespace types;
using namespace deserializer;
using namespace serializer;

int main() {
    std::string test_json {R"([
  {
    "nameHash": "VEHICLE_WEAPON_ARDENT_MG",
    "hash": -1001503935,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_AR_MG",
    "gxtDescription": "WTD_V_AR_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_INSURGENT_MINIGUN",
    "hash": -1433899528,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_INS_MINI",
    "gxtDescription": "WTD_V_INS_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MOBILEOPS_CANNON",
    "hash": -448894556,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_MOBILEOPS_CANNON",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_NIGHTSHARK_MG",
    "hash": -1508194956,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_NS_MG",
    "gxtDescription": "WTD_V_NS_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TECHNICAL_MINIGUN",
    "hash": -611760632,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TEC_MINI",
    "gxtDescription": "WTD_V_TEC_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AKULA_TURRET_SINGLE",
    "hash": -1246512723,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_AKU_TS",
    "gxtDescription": "WTD_V_AKU_TS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AKULA_TURRET_DUAL",
    "hash": 476907586,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_AKU_TD",
    "gxtDescription": "WTD_V_AKU_TD",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AKULA_MINIGUN",
    "hash": 431576697,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_AKU_MN",
    "gxtDescription": "WTD_V_AKU_MN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AKULA_MISSILE",
    "hash": 2092838988,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HUNTER_MISSILE",
    "gxtName": "WT_V_AKU_MI",
    "gxtDescription": "WTD_V_AKU_MI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AKULA_BARRAGE",
    "hash": -2012408590,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HUNTER_BARRAGE",
    "gxtName": "WT_V_AKU_BA",
    "gxtDescription": "WTD_V_AKU_BA",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_APC_CANNON",
    "hash": 328167896,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_APC_CANNON",
    "gxtName": "WT_V_APC_C",
    "gxtDescription": "WTD_V_APC_C",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_APC_MISSILE",
    "hash": 1151689097,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_APC_MISSILE",
    "gxtName": "WT_V_APC_M",
    "gxtDescription": "WTD_V_APC_M",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_APC_MG",
    "hash": 190244068,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_APC_S",
    "gxtDescription": "WTD_V_APC_S",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_AVENGER_CANNON",
    "hash": -1738072005,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_AVENGER_CANNON",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BARRAGE_TOP_MG",
    "hash": -146175596,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_BAR_TMG",
    "gxtDescription": "WTD_V_BAR_TMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BARRAGE_TOP_MINIGUN",
    "hash": 1000258817,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_BAR_TMI",
    "gxtDescription": "WTD_V_BAR_TMI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BARRAGE_REAR_MG",
    "hash": 1200179045,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_BAR_RMG",
    "gxtDescription": "WTD_V_BAR_RMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BARRAGE_REAR_MINIGUN",
    "hash": 525623141,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_BAR_RMI",
    "gxtDescription": "WTD_V_BAR_RMI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BARRAGE_REAR_GL",
    "hash": -1538514291,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_BARRAGE_GL",
    "gxtName": "WT_V_BAR_RGL",
    "gxtDescription": "WTD_V_BAR_RGL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMB",
    "hash": -1695500020,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_smug_bomb_01",
    "ammo": "AMMO_VEHICLEBOMB",
    "gxtName": "WT_VEHBOMB",
    "gxtDescription": "WTD_VEHBOMB",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMB_CLUSTER",
    "hash": 220773539,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_smug_bomb_02",
    "ammo": "AMMO_VEHICLEBOMB_CLUSTER",
    "gxtName": "WT_VEHBOMB_C",
    "gxtDescription": "WTD_VEHBOMB_C",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMB_GAS",
    "hash": 1430300958,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_smug_bomb_03",
    "ammo": "AMMO_VEHICLEBOMB_GAS",
    "gxtName": "WT_VEHBOMB_G",
    "gxtDescription": "WTD_VEHBOMB_G",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMB_INCENDIARY",
    "hash": 1794615063,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_smug_bomb_04",
    "ammo": "AMMO_VEHICLEBOMB_INCENDIARY",
    "gxtName": "WT_VEHBOMB_I",
    "gxtDescription": "WTD_VEHBOMB_I",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMBUSHKA_CANNON",
    "hash": -666617255,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_BSHK_CANN",
    "gxtDescription": "WTD_V_BSHK_CANN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMBUSHKA_DUALMG",
    "hash": 741027160,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_BSHK_DUAL",
    "gxtDescription": "WTD_V_BSHK_DUAL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BRUISER_50CAL",
    "hash": -683817471,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BRUISER2_50CAL_LASER",
    "hash": 1030357398,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_CARACARA_MG",
    "hash": 1817275304,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_CARACARA_MINIGUN",
    "hash": 1338760315,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TEC_MINI",
    "gxtDescription": "WTD_V_TEC_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_CHERNO_MISSILE",
    "hash": -1572351938,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_CHERNO_MISSILE",
    "gxtName": "WT_V_CHE_MI",
    "gxtDescription": "WTD_V_CHE_MI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DEATHBIKE_DUALMINIGUN",
    "hash": 490982948,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_DBK_MINI",
    "gxtDescription": "WTD_V_DBK_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DEATHBIKE2_MINIGUN_LASER",
    "hash": -385086487,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DELUXO_MG",
    "hash": -1694538890,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_DEL_MG",
    "gxtDescription": "WTD_V_DEL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DELUXO_MISSILE",
    "hash": -1258723020,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_OPPRESSOR_MISSILE",
    "gxtName": "WT_V_DEL_MI",
    "gxtDescription": "WTD_V_DEL_MI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DOGFIGHTER_MG",
    "hash": 1595421922,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_DGF_MG",
    "gxtDescription": "WTD_V_DGF_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DOGFIGHTER_MISSILE",
    "hash": -901318531,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_DGF_MISS",
    "gxtDescription": "WTD_V_DGF_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DUNE_MG",
    "hash": -787150897,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_DU_MG",
    "gxtDescription": "WTD_V_DU_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DUNE_GRENADELAUNCHER",
    "hash": -1594068723,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_DUNE_GRENADELAUNCHER",
    "gxtName": "WT_V_DU_GL",
    "gxtDescription": "WTD_V_DU_GL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DUNE_MINIGUN",
    "hash": 1416047217,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_DU_MINI",
    "gxtDescription": "WTD_V_DU_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_FLAMETHROWER",
    "hash": -1291819974,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_FLAME",
    "gxtDescription": "WTD_V_FLAME",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_FLAMETHROWER_SCIFI",
    "hash": -2112637790,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_FLAME",
    "gxtDescription": "WTD_V_FLAME",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HACKER_MISSILE",
    "hash": 1987049393,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HACKER_MISSILE",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HACKER_MISSILE_HOMING",
    "hash": 2011877270,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HACKER_MISSILE",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HALFTRACK_DUALMG",
    "hash": 1331922171,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_HT_DUALMG",
    "gxtDescription": "WTD_V_HT_DUALMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HALFTRACK_QUADMG",
    "hash": 1226518132,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_HT_QUADMG",
    "gxtDescription": "WTD_V_HT_QUADMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HAVOK_MINIGUN",
    "hash": 855547631,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_HAV_MINI",
    "gxtDescription": "WTD_V_HAV_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HUNTER_MG",
    "hash": 1119518887,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_HUNT_MG",
    "gxtDescription": "WTD_V_HUNT_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HUNTER_MISSILE",
    "hash": 153396725,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HUNTER_MISSILE",
    "gxtName": "WT_V_HUNT_MISS",
    "gxtDescription": "WTD_V_HUNT_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HUNTER_BARRAGE",
    "hash": 785467445,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_HUNTER_BARRAGE",
    "gxtName": "WT_V_HUNT_BARR",
    "gxtDescription": "WTD_V_HUNT_BARR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_HUNTER_CANNON",
    "hash": 704686874,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_HUNT_CANN",
    "gxtDescription": "WTD_V_HUNT_CANN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ISSI4_50CAL",
    "hash": 1984488269,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ISSI5_50CAL_LASER",
    "hash": 1988061477,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_KHANJALI_CANNON",
    "hash": 507170720,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_TANK",
    "gxtName": "WT_V_KHA_CA",
    "gxtDescription": "WTD_V_KHA_CA",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_KHANJALI_CANNON_HEAVY",
    "hash": -2088013459,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_KHANJALI_CANNON_HEAVY",
    "gxtName": "WT_V_KHA_HCA",
    "gxtDescription": "WTD_V_KHA_HCA",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_KHANJALI_MG",
    "hash": 711953949,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_KHA_MG",
    "gxtDescription": "WTD_V_KHA_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_KHANJALI_GL",
    "hash": 394659298,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_KHANJALI_GL",
    "gxtName": "WT_V_KHA_GL",
    "gxtDescription": "WTD_V_KHA_GL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MENACER_MG",
    "hash": -540346204,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_NS_MG",
    "gxtDescription": "WTD_V_NS_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MICROLIGHT_MG",
    "hash": -991944340,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_MCRL_MG",
    "gxtDescription": "WTD_V_MCRL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE",
    "hash": 1508567460,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_KINETIC",
    "hash": 1007245390,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE_KINETIC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_EMP",
    "hash": 1776356704,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE_EMP",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_SPIKE",
    "hash": -647126932,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE_SPIKE",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_SLICK",
    "hash": 1459276487,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE_SLICK",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_TAR",
    "hash": -197031008,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_vehiclemine",
    "ammo": "AMMO_VEHICLEMINE_TAR",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_KINETIC_RC",
    "hash": 623572320,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_arena_landmine_01b",
    "ammo": "AMMO_VEHICLEMINE_KINETIC_RC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_EMP_RC",
    "hash": 1414837446,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_arena_landmine_01b",
    "ammo": "AMMO_VEHICLEMINE_EMP_RC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_SPIKE_RC",
    "hash": 2083192401,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_arena_landmine_01b",
    "ammo": "AMMO_VEHICLEMINE_SPIKE_RC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_SLICK_RC",
    "hash": -2065138921,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_arena_landmine_01b",
    "ammo": "AMMO_VEHICLEMINE_SLICK_RC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MINE_TAR_RC",
    "hash": 2100589782,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_arena_landmine_01b",
    "ammo": "AMMO_VEHICLEMINE_TAR_RC",
    "gxtName": "WT_VEHMINE",
    "gxtDescription": "WTD_VEHMINE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MOGUL_NOSE",
    "hash": -166158518,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MOG_NOSE",
    "gxtDescription": "WTD_V_MOG_NOSE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MOGUL_DUALNOSE",
    "hash": -437014993,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MOG_DNOSE",
    "gxtDescription": "WTD_V_MOG_DNOSE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MOGUL_TURRET",
    "hash": -486730914,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_MOG_TURR",
    "gxtDescription": "WTD_V_MOG_TURR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MOGUL_DUALTURRET",
    "hash": -1171817471,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_MOG_DTURR",
    "gxtDescription": "WTD_V_MOG_DTURR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MONSTER3_GLKIN",
    "hash": -441560099,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_MONSTER3_KINETIC",
    "gxtName": "WT_V_GREN_KIN",
    "gxtDescription": "WTD_V_GREN_KIN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MORTAR_EXPLOSIVE",
    "hash": -1582773038,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_MORTAR_EXPLOSIVE",
    "gxtName": "WT_V_TAM_MORT",
    "gxtDescription": "WTD_V_TAM_MORT",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MORTAR_KINETIC",
    "hash": 1663705853,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_MORTAR_KINETIC",
    "gxtName": "WT_V_MORTAR_KIN",
    "gxtDescription": "WTD_V_MORTAR_KIN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MULE4_MG",
    "hash": -2074769625,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MULE4_MISSILE",
    "hash": 1198717003,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_TAM_MISS",
    "gxtDescription": "WTD_V_TAM_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_MULE4_TURRET_GL",
    "hash": -586003867,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_MULE4_GL",
    "gxtName": "WT_V_KHA_GL",
    "gxtDescription": "WTD_V_KHA_GL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_OPPRESSOR_MG",
    "hash": -651022627,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_OP_MG",
    "gxtDescription": "WTD_V_OP_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_OPPRESSOR_MISSILE",
    "hash": -1950890434,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_OPPRESSOR_MISSILE",
    "gxtName": "WT_V_OP_MISS",
    "gxtDescription": "WTD_V_OP_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_OPPRESSOR2_MG",
    "hash": -498786858,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_OP_MG",
    "gxtDescription": "WTD_V_OP_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_OPPRESSOR2_CANNON",
    "hash": -699583383,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_ROG_CANN",
    "gxtDescription": "WTD_V_ROG_CANN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_OPPRESSOR2_MISSILE",
    "hash": 1966766321,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_OPPRESSOR2_MISSILE",
    "gxtName": "WT_V_OP_MISS",
    "gxtDescription": "WTD_V_OP_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PARAGON2_MG",
    "hash": 749486726,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_POUNDER2_MINI",
    "hash": -2031683506,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_POUNDER2_MISSILE",
    "hash": 162065050,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_TAM_MISS",
    "gxtDescription": "WTD_V_TAM_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_POUNDER2_BARRAGE",
    "hash": -1838445340,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_POUNDER2_MISSILE",
    "gxtName": "WT_V_POU_BA",
    "gxtDescription": "WTD_V_POU_BA",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_POUNDER2_GL",
    "hash": -1827078378,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_POUNDER2_GL",
    "gxtName": "WT_V_KHA_GL",
    "gxtDescription": "WTD_V_KHA_GL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ROGUE_MG",
    "hash": 158495693,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_ROG_MG",
    "gxtDescription": "WTD_V_ROG_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ROGUE_CANNON",
    "hash": -416629822,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_ROG_CANN",
    "gxtDescription": "WTD_V_ROG_CANN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ROGUE_MISSILE",
    "hash": 1820910717,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_ROGUE_MISSILE",
    "gxtName": "WT_V_ROG_MISS",
    "gxtDescription": "WTD_V_ROG_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SCARAB_50CAL",
    "hash": 562032424,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_1",
    "gxtDescription": "WTD_V_MG50_1",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SCARAB2_50CAL_LASER",
    "hash": -500306484,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_1L",
    "gxtDescription": "WTD_V_MG50_1L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SCRAMJET_MG",
    "hash": 231629074,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_VGL_MG",
    "gxtDescription": "WTD_V_VGL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SCRAMJET_MISSILE",
    "hash": -1125578533,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SCRAMJET_MISSILE",
    "gxtName": "WT_V_VGL_MISS",
    "gxtDescription": "WTD_V_VGL_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SEABREEZE_MG",
    "hash": 1371067624,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_SBZ_MG",
    "gxtDescription": "WTD_V_SBZ_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SPEEDO4_MG",
    "hash": -939722436,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SPEEDO4_TURRET_MG",
    "hash": -699002559,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_SPD_TMG",
    "gxtDescription": "WTD_V_SPD_TMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SPEEDO4_TURRET_MINI",
    "hash": -1627504966,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_SPD_TMI",
    "gxtDescription": "WTD_V_SPD_TMI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_STRIKEFORCE_BARRAGE",
    "hash": 968648323,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_STRIKEFORCE_BARRAGE",
    "gxtName": "WT_V_HUNT_BARR",
    "gxtDescription": "WTD_V_HUNT_BARR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_STRIKEFORCE_CANNON",
    "hash": 955522731,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_ROG_CANN",
    "gxtDescription": "WTD_V_ROG_CANN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_STRIKEFORCE_MISSILE",
    "hash": 519052682,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_STRIKEFORCE_MISSILE",
    "gxtName": "WT_V_HUNT_MISS",
    "gxtDescription": "WTD_V_HUNT_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SUBCAR_MG",
    "hash": 1176362416,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_SUB_MG",
    "gxtDescription": "WTD_V_SUB_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SUBCAR_MISSILE",
    "hash": -729187314,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SUBCAR_MISSILE",
    "gxtName": "WT_V_SUB_MI",
    "gxtDescription": "WTD_V_SUB_MI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SUBCAR_TORPEDO",
    "hash": -410795078,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SUBCAR_TORPEDO",
    "gxtName": "WT_V_SUB_TO",
    "gxtDescription": "WTD_V_SUB_TO",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TAMPA_MISSILE",
    "hash": -1638383454,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_TAM_MISS",
    "gxtDescription": "WTD_V_TAM_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TAMPA_MORTAR",
    "hash": 1015268368,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_TAMPA_MORTAR",
    "gxtName": "WT_V_TAM_MORT",
    "gxtDescription": "WTD_V_TAM_MORT",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TAMPA_FIXEDMINIGUN",
    "hash": -624592211,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TAM_FMINI",
    "gxtDescription": "WTD_V_TAM_FMINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TAMPA_DUALMINIGUN",
    "hash": 1744687076,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TAM_DMINI",
    "gxtDescription": "WTD_V_TAM_DMINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_THRUSTER_MG",
    "hash": 1697521053,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_THR_MG",
    "gxtDescription": "WTD_V_THR_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_THRUSTER_MISSILE",
    "hash": 1177935125,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_THRUSTER_MISSILE",
    "gxtName": "WT_V_THR_MI",
    "gxtDescription": "WTD_V_THR_MI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TRAILER_QUADMG",
    "hash": 1192341548,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TR_QUADMG",
    "gxtDescription": "WTD_V_TR_QUADMG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TRAILER_DUALAA",
    "hash": -2138288820,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_TRAILER_AA",
    "gxtName": "WT_V_TR_DUALAA",
    "gxtDescription": "WTD_V_TR_DUALAA",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TRAILER_MISSILE",
    "hash": 341154295,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_TRAILER_MISSILE",
    "gxtName": "WT_V_TR_MISS",
    "gxtDescription": "WTD_V_TR_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TULA_NOSEMG",
    "hash": 1100844565,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TUL_NOSE",
    "gxtDescription": "WTD_V_TUL_NOSE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TULA_MG",
    "hash": 1217122433,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TUL_MG",
    "gxtDescription": "WTD_V_TUL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TULA_DUALMG",
    "hash": -1328456693,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TUL_DUAL",
    "gxtDescription": "WTD_V_TUL_DUAL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TULA_MINIGUN",
    "hash": 376489128,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TUL_MINI",
    "gxtDescription": "WTD_V_TUL_MINI",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_VIGILANTE_MG",
    "hash": -200835353,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_VGL_MG",
    "gxtDescription": "WTD_V_VGL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_VIGILANTE_MISSILE",
    "hash": 1347266149,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_VIGILANTE_MISSILE",
    "gxtName": "WT_V_VGL_MISS",
    "gxtDescription": "WTD_V_VGL_MISS",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BOMB_STANDARD_WIDE",
    "hash": 1856325840,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_smug_bomb_01",
    "ammo": "AMMO_VEHICLEBOMB_WIDE",
    "gxtName": "WT_VEHBOMB",
    "gxtDescription": "WTD_VEHBOMB",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_VOLATOL_DUALMG",
    "hash": 1150790720,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_VOL_MG",
    "gxtDescription": "WTD_V_VOL_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_COMET_MG",
    "hash": -358074893,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_REVOLTER_MG",
    "hash": -1117887894,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SAVESTRA_MG",
    "hash": -348002226,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_VISERIS_MG",
    "hash": -2019545594,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_IMPALER2_50CAL",
    "hash": 1599495177,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_IMPALER3_50CAL_LASER",
    "hash": -1933706104,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_IMPERATOR_50CAL",
    "hash": -1235040645,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_IMPERATOR2_50CAL_LASER",
    "hash": 2014823718,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DOMINATOR4_50CAL",
    "hash": -133391601,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_DOMINATOR5_50CAL_LASER",
    "hash": -1272681889,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SLAMVAN4_50CAL",
    "hash": 984313451,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SLAMVAN5_50CAL_LASER",
    "hash": 1368736686,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BRUTUS_50CAL",
    "hash": -346137590,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_1",
    "gxtDescription": "WTD_V_MG50_1",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_BRUTUS2_50CAL_LASER",
    "hash": 1757914307,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_1L",
    "gxtDescription": "WTD_V_MG50_1L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ZR380_50CAL",
    "hash": 1790524546,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2",
    "gxtDescription": "WTD_V_MG50_2",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ZR3802_50CAL_LASER",
    "hash": 570463164,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_MG50_2L",
    "gxtDescription": "WTD_V_MG50_2L",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_JB700_MG",
    "hash": 926602556,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_COM_MG",
    "gxtDescription": "WTD_V_COM_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RCTANK_GUN",
    "hash": 1392289305,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_RCT_MG",
    "gxtDescription": "WTD_V_RCT_MG",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RCTANK_FLAME",
    "hash": -185710198,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_RCT_FL",
    "gxtDescription": "WTD_V_RCT_FL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RCTANK_ROCKET",
    "hash": 1995916491,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_RCTANK_ROCKET",
    "gxtName": "WT_V_RCT_RK",
    "gxtDescription": "WTD_V_RCT_RK",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RCTANK_LAZER",
    "hash": 1475488848,
    "clipSize": 15000,
    "group": "GROUP_HEAVY",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_RCT_LZ",
    "gxtDescription": "WTD_V_RCT_LZ",
    "components": []
  },
  {
    "nameHash": "WEAPON_AIR_DEFENCE_GUN",
    "hash": 738733437,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "WEAPON_AUTOSHOTGUN",
    "hash": 317205821,
    "clipSize": 10,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_sweeper",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_AUTOSHGN",
    "gxtDescription": "WTD_AUTOSHGN",
    "components": [
      {
        "nameHash": "COMPONENT_AUTOSHOTGUN_CLIP_01",
        "hash": 169463950,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_BATTLEAXE",
    "hash": -853065399,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_battleaxe",
    "ammo": "NULL",
    "gxtName": "WT_BATTLEAXE",
    "gxtDescription": "WTD_BATTLEAXE",
    "components": []
  },
  {
    "nameHash": "WEAPON_BOTTLE",
    "hash": -102323637,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_bottle",
    "ammo": "NULL",
    "gxtName": "WT_BOTTLE",
    "gxtDescription": "WTD_BOTTLE",
    "components": []
  },
  {
    "nameHash": "WEAPON_BULLPUPRIFLE",
    "hash": 2132975508,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_bullpuprifle",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_BULLRIFLE",
    "gxtDescription": "WTD_BULLRIFLE",
    "components": [
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_CLIP_01",
        "hash": -979292288,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_CLIP_02",
        "hash": -1284994289,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL",
        "hash": -1439939148,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      }
    ]
  },
  {
    "nameHash": "VEHICLE_WEAPON_CANNON_BLAZER",
    "hash": -335937730,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "WEAPON_COMBATPDW",
    "hash": 171789620,
    "clipSize": 30,
    "group": "GROUP_SMG",
    "model": "W_SB_PDW",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_COMBATPDW",
    "gxtDescription": "WTD_COMBATPDW",
    "components": [
      {
        "nameHash": "COMPONENT_COMBATPDW_CLIP_01",
        "hash": 1125642654,
        "isDefault": true,
        "attachBone": "WAPClip_2"
      },
      {
        "nameHash": "COMPONENT_COMBATPDW_CLIP_02",
        "hash": 860508675,
        "isDefault": false,
        "attachBone": "WAPClip_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL",
        "hash": -1439939148,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_COMPACTLAUNCHER",
    "hash": 125959754,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_compactgl",
    "ammo": "AMMO_GRENADELAUNCHER",
    "gxtName": "WT_CMPGL",
    "gxtDescription": "WTD_CMPGL",
    "components": [
      {
        "nameHash": "COMPONENT_COMPACTLAUNCHER_CLIP_01",
        "hash": 1235472140,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_COMPACTRIFLE",
    "hash": 1649403952,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_assaultrifle_smg",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_CMPRIFLE",
    "gxtDescription": "WTD_CMPRIFLE",
    "components": [
      {
        "nameHash": "COMPONENT_COMPACTRIFLE_CLIP_01",
        "hash": 1363085923,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMPACTRIFLE_CLIP_02",
        "hash": 1509923832,
        "isDefault": false,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_DAGGER",
    "hash": -1834847097,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_dagger",
    "ammo": "NULL",
    "gxtName": "WT_DAGGER",
    "gxtDescription": "WTD_DAGGER",
    "components": []
  },
  {
    "nameHash": "WEAPON_DBSHOTGUN",
    "hash": -275439685,
    "clipSize": 2,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_doublebarrel",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_DBSHGN",
    "gxtDescription": "WTD_DBSHGN",
    "components": [
      {
        "nameHash": "COMPONENT_DBSHOTGUN_CLIP_01",
        "hash": 703231006,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_FIREWORK",
    "hash": 2138347493,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_firework",
    "ammo": "AMMO_FIREWORK",
    "gxtName": "WT_FIREWRK",
    "gxtDescription": "WTD_FIREWRK",
    "components": [
      {
        "nameHash": "COMPONENT_FIREWORK_CLIP_01",
        "hash": -454770035,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_FLAREGUN",
    "hash": 1198879012,
    "clipSize": 1,
    "group": "GROUP_PISTOL",
    "model": "w_pi_flaregun",
    "ammo": "AMMO_FLAREGUN",
    "gxtName": "WT_FLAREGUN",
    "gxtDescription": "WTD_FLAREGUN",
    "components": [
      {
        "nameHash": "COMPONENT_FLAREGUN_CLIP_01",
        "hash": -1813398119,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_FLASHLIGHT",
    "hash": -1951375401,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_flashlight",
    "ammo": "NULL",
    "gxtName": "WT_FLASHLIGHT",
    "gxtDescription": "WTD_FLASHLIGHT",
    "components": [
      {
        "nameHash": "COMPONENT_FLASHLIGHT_LIGHT",
        "hash": -575194865,
        "isDefault": true,
        "attachBone": "WAPFlsh"
      }
    ]
  },
  {
    "nameHash": "WEAPON_GARBAGEBAG",
    "hash": -499989876,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_KNIFE",
    "gxtDescription": "WTD_KNIFE",
    "components": []
  },
  {
    "nameHash": "WEAPON_GUSENBERG",
    "hash": 1627465347,
    "clipSize": 30,
    "group": "GROUP_MG",
    "model": "w_sb_gusenberg",
    "ammo": "AMMO_MG",
    "gxtName": "WT_GUSNBRG",
    "gxtDescription": "WTD_GUSNBRG",
    "components": [
      {
        "nameHash": "COMPONENT_GUSENBERG_CLIP_01",
        "hash": 484812453,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_GUSENBERG_CLIP_02",
        "hash": -355941776,
        "isDefault": false,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HANDCUFFS",
    "hash": -800287667,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_KNIFE",
    "gxtDescription": "WTD_KNIFE",
    "components": []
  },
  {
    "nameHash": "WEAPON_HATCHET",
    "hash": -102973651,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_hatchet",
    "ammo": "NULL",
    "gxtName": "WT_HATCHET",
    "gxtDescription": "WTD_HATCHET",
    "components": []
  },
  {
    "nameHash": "WEAPON_HEAVYPISTOL",
    "hash": -771403250,
    "clipSize": 18,
    "group": "GROUP_PISTOL",
    "model": "w_pi_heavypistol",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_HVYPISTOL",
    "gxtDescription": "WTD_HVYPISTOL",
    "components": [
      {
        "nameHash": "COMPONENT_HEAVYPISTOL_CLIP_01",
        "hash": 222992026,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYPISTOL_CLIP_02",
        "hash": 1694090795,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HEAVYSHOTGUN",
    "hash": 984333226,
    "clipSize": 6,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_heavyshotgun",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_HVYSHGN",
    "gxtDescription": "WTD_HVYSHGN",
    "components": [
      {
        "nameHash": "COMPONENT_HEAVYSHOTGUN_CLIP_01",
        "hash": 844049759,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSHOTGUN_CLIP_02",
        "hash": -1759709443,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HOMINGLAUNCHER",
    "hash": 1672152130,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_homing",
    "ammo": "AMMO_HOMINGLAUNCHER",
    "gxtName": "WT_HOMLNCH",
    "gxtDescription": "WTD_HOMLNCH",
    "components": [
      {
        "nameHash": "COMPONENT_HOMINGLAUNCHER_CLIP_01",
        "hash": -132960961,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_KNUCKLE",
    "hash": -656458692,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "W_ME_Knuckle",
    "ammo": "NULL",
    "gxtName": "WT_KNUCKLE",
    "gxtDescription": "WTD_KNUCKLE",
    "components": [
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_BASE",
        "hash": -213504205,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_PIMP",
        "hash": -971770235,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_BALLAS",
        "hash": -287703709,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_DOLLAR",
        "hash": 1351683121,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_DIAMOND",
        "hash": -1755194916,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_HATE",
        "hash": 2112683568,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_LOVE",
        "hash": 1062111910,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_PLAYER",
        "hash": 146278587,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_KING",
        "hash": -494162961,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_KNUCKLE_VARMOD_VAGOS",
        "hash": 2062808965,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MACHETE",
    "hash": -581044007,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_machette_lr",
    "ammo": "NULL",
    "gxtName": "WT_MACHETE",
    "gxtDescription": "WTD_MACHETE",
    "components": []
  },
  {
    "nameHash": "WEAPON_MACHINEPISTOL",
    "hash": -619010992,
    "clipSize": 12,
    "group": "GROUP_SMG",
    "model": "w_sb_compactsmg",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_MCHPIST",
    "gxtDescription": "WTD_MCHPIST",
    "components": [
      {
        "nameHash": "COMPONENT_MACHINEPISTOL_CLIP_01",
        "hash": 1198425599,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MACHINEPISTOL_CLIP_02",
        "hash": -1188271751,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MARKSMANPISTOL",
    "hash": -598887786,
    "clipSize": 1,
    "group": "GROUP_PISTOL",
    "model": "W_PI_SingleShot",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_MKPISTOL",
    "gxtDescription": "WTD_MKPISTOL",
    "components": [
      {
        "nameHash": "COMPONENT_MARKSMANPISTOL_CLIP_01",
        "hash": -878820883,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MARKSMANRIFLE",
    "hash": -952879014,
    "clipSize": 8,
    "group": "GROUP_SNIPER",
    "model": "w_sr_marksmanrifle",
    "ammo": "AMMO_SNIPER",
    "gxtName": "WT_MKRIFLE",
    "gxtDescription": "WTD_MKRIFLE",
    "components": [
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_CLIP_01",
        "hash": -667205311,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_CLIP_02",
        "hash": -855823675,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM",
        "hash": 471997210,
        "isDefault": true,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MINISMG",
    "hash": -1121678507,
    "clipSize": 20,
    "group": "GROUP_SMG",
    "model": "w_sb_minismg",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_MINISMG",
    "gxtDescription": "WTD_MINISMG",
    "components": [
      {
        "nameHash": "COMPONENT_MINISMG_CLIP_01",
        "hash": -2067221805,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MINISMG_CLIP_02",
        "hash": -1820405577,
        "isDefault": false,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MUSKET",
    "hash": -1466123874,
    "clipSize": 1,
    "group": "GROUP_SNIPER",
    "model": "w_ar_musket",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_MUSKET",
    "gxtDescription": "WTD_MUSKET",
    "components": [
      {
        "nameHash": "COMPONENT_MUSKET_CLIP_01",
        "hash": 1322387263,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PIPEBOMB",
    "hash": -1169823560,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_pipebomb",
    "ammo": "AMMO_PIPEBOMB",
    "gxtName": "WT_PIPEBOMB",
    "gxtDescription": "WTD_PIPEBOMB",
    "components": []
  },
  {
    "nameHash": "WEAPON_POOLCUE",
    "hash": -1810795771,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_poolcue",
    "ammo": "NULL",
    "gxtName": "WT_POOLCUE",
    "gxtDescription": "WTD_POOLCUE",
    "components": []
  },
  {
    "nameHash": "WEAPON_PROXMINE",
    "hash": -1420407917,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_apmine",
    "ammo": "AMMO_PROXMINE",
    "gxtName": "WT_PRXMINE",
    "gxtDescription": "WTD_PRXMINE",
    "components": []
  },
  {
    "nameHash": "WEAPON_RAILGUN",
    "hash": 1834241177,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_ar_railgun",
    "ammo": "AMMO_RAILGUN",
    "gxtName": "WT_RAILGUN",
    "gxtDescription": "WTD_RAILGUN",
    "components": [
      {
        "nameHash": "COMPONENT_RAILGUN_CLIP_01",
        "hash": 59044840,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_REVOLVER",
    "hash": -1045183535,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_revolver",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_REVOLVER",
    "gxtDescription": "WTD_REVOLVER",
    "components": [
      {
        "nameHash": "COMPONENT_REVOLVER_CLIP_01",
        "hash": -377062173,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_VARMOD_BOSS",
        "hash": 384708672,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_VARMOD_GOON",
        "hash": -1802258419,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_UNARMED",
    "hash": -1569615261,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_UNARMED",
    "gxtDescription": "WTD_UNARMED",
    "components": []
  },
  {
    "nameHash": "WEAPON_ANIMAL",
    "hash": -100946242,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_COUGAR",
    "hash": 148160082,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_KNIFE",
    "hash": -1716189206,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_knife_01",
    "ammo": "NULL",
    "gxtName": "WT_KNIFE",
    "gxtDescription": "WTD_KNIFE",
    "components": []
  },
  {
    "nameHash": "WEAPON_NIGHTSTICK",
    "hash": 1737195953,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_nightstick",
    "ammo": "NULL",
    "gxtName": "WT_NGTSTK",
    "gxtDescription": "WTD_NGTSTK",
    "components": []
  },
  {
    "nameHash": "WEAPON_HAMMER",
    "hash": 1317494643,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_hammer",
    "ammo": "NULL",
    "gxtName": "WT_HAMMER",
    "gxtDescription": "WTD_HAMMER",
    "components": []
  },
  {
    "nameHash": "WEAPON_BAT",
    "hash": -1786099057,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_bat",
    "ammo": "NULL",
    "gxtName": "WT_BAT",
    "gxtDescription": "WTD_BAT",
    "components": []
  },
  {
    "nameHash": "WEAPON_GOLFCLUB",
    "hash": 1141786504,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_gclub",
    "ammo": "NULL",
    "gxtName": "WT_GOLFCLUB",
    "gxtDescription": "WTD_GOLFCLUB",
    "components": []
  },
  {
    "nameHash": "WEAPON_CROWBAR",
    "hash": -2067956739,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_crowbar",
    "ammo": "NULL",
    "gxtName": "WT_CROWBAR",
    "gxtDescription": "WTD_CROWBAR",
    "components": []
  },
  {
    "nameHash": "WEAPON_PISTOL",
    "hash": 453432689,
    "clipSize": 12,
    "group": "GROUP_PISTOL",
    "model": "W_PI_PISTOL",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_PIST",
    "gxtDescription": "WTD_PIST",
    "components": [
      {
        "nameHash": "COMPONENT_PISTOL_CLIP_01",
        "hash": -19858063,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_CLIP_02",
        "hash": -316253668,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP_02",
        "hash": 1709866683,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_PISTOL_VARMOD_LUXE",
        "hash": -684126074,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_COMBATPISTOL",
    "hash": 1593441988,
    "clipSize": 12,
    "group": "GROUP_PISTOL",
    "model": "W_PI_COMBATPISTOL",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_PIST_CBT",
    "gxtDescription": "WTD_PIST_CBT",
    "components": [
      {
        "nameHash": "COMPONENT_COMBATPISTOL_CLIP_01",
        "hash": 119648377,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATPISTOL_CLIP_02",
        "hash": -696561875,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_COMBATPISTOL_VARMOD_LOWRIDER",
        "hash": -966439566,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_APPISTOL",
    "hash": 584646201,
    "clipSize": 18,
    "group": "GROUP_PISTOL",
    "model": "W_PI_APPISTOL",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_PIST_AP",
    "gxtDescription": "WTD_PIST_AP",
    "components": [
      {
        "nameHash": "COMPONENT_APPISTOL_CLIP_01",
        "hash": 834974250,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_APPISTOL_CLIP_02",
        "hash": 614078421,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_APPISTOL_VARMOD_LUXE",
        "hash": -1686714580,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PISTOL50",
    "hash": -1716589765,
    "clipSize": 9,
    "group": "GROUP_PISTOL",
    "model": "W_PI_PISTOL50",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_PIST_50",
    "gxtDescription": "WTD_PIST_50",
    "components": [
      {
        "nameHash": "COMPONENT_PISTOL50_CLIP_01",
        "hash": 580369945,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL50_CLIP_02",
        "hash": -640439150,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_PISTOL50_VARMOD_LUXE",
        "hash": 2008591151,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MICROSMG",
    "hash": 324215364,
    "clipSize": 16,
    "group": "GROUP_SMG",
    "model": "w_sb_microsmg",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_SMG_MCR",
    "gxtDescription": "WTD_SMG_MCR",
    "components": [
      {
        "nameHash": "COMPONENT_MICROSMG_CLIP_01",
        "hash": -884429072,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MICROSMG_CLIP_02",
        "hash": 283556395,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO",
        "hash": -1657815255,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_MICROSMG_VARMOD_LUXE",
        "hash": 1215999497,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SMG",
    "hash": 736523883,
    "clipSize": 30,
    "group": "GROUP_SMG",
    "model": "w_sb_smg",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_SMG",
    "gxtDescription": "WTD_SMG",
    "components": [
      {
        "nameHash": "COMPONENT_SMG_CLIP_01",
        "hash": 643254679,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_CLIP_02",
        "hash": 889808635,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_CLIP_03",
        "hash": 2043113590,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_02",
        "hash": 1019656791,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_SMG_VARMOD_LUXE",
        "hash": 663170192,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_ASSAULTSMG",
    "hash": -270015777,
    "clipSize": 30,
    "group": "GROUP_SMG",
    "model": "w_sb_assaultsmg",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_SMG_ASL",
    "gxtDescription": "WTD_SMG_ASL",
    "components": [
      {
        "nameHash": "COMPONENT_ASSAULTSMG_CLIP_01",
        "hash": -1928132688,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTSMG_CLIP_02",
        "hash": -1152981993,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO",
        "hash": -1657815255,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_ASSAULTSMG_VARMOD_LOWRIDER",
        "hash": 663517359,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_ASSAULTRIFLE",
    "hash": -1074790547,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "W_AR_ASSAULTRIFLE",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_RIFLE_ASL",
    "gxtDescription": "WTD_RIFLE_ASL",
    "components": [
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_CLIP_01",
        "hash": -1101075946,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_CLIP_02",
        "hash": -1323216997,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_CLIP_03",
        "hash": -604986051,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO",
        "hash": -1657815255,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_VARMOD_LUXE",
        "hash": 1319990579,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_CARBINERIFLE",
    "hash": -2084633992,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "W_AR_CARBINERIFLE",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_RIFLE_CBN",
    "gxtDescription": "WTD_RIFLE_CBN",
    "components": [
      {
        "nameHash": "COMPONENT_CARBINERIFLE_CLIP_01",
        "hash": -1614924820,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_CLIP_02",
        "hash": -1861183855,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_CLIP_03",
        "hash": -1167922891,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_RAILCOVER_01",
        "hash": 1967214384,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM",
        "hash": -1596416958,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_VARMOD_LUXE",
        "hash": -660892072,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_ADVANCEDRIFLE",
    "hash": -1357824103,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "W_AR_ADVANCEDRIFLE",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_RIFLE_ADV",
    "gxtDescription": "WTD_RIFLE_ADV",
    "components": [
      {
        "nameHash": "COMPONENT_ADVANCEDRIFLE_CLIP_01",
        "hash": -91250417,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ADVANCEDRIFLE_CLIP_02",
        "hash": -1899902599,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL",
        "hash": -1439939148,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_ADVANCEDRIFLE_VARMOD_LUXE",
        "hash": 930927479,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MG",
    "hash": -1660422300,
    "clipSize": 54,
    "group": "GROUP_MG",
    "model": "w_mg_mg",
    "ammo": "AMMO_MG",
    "gxtName": "WT_MG",
    "gxtDescription": "WTD_MG",
    "components": [
      {
        "nameHash": "COMPONENT_MG_CLIP_01",
        "hash": -197857404,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MG_CLIP_02",
        "hash": -2112517305,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL_02",
        "hash": 1006677997,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_MG_VARMOD_LOWRIDER",
        "hash": -690308418,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_COMBATMG",
    "hash": 2144741730,
    "clipSize": 100,
    "group": "GROUP_MG",
    "model": "w_mg_combatmg",
    "ammo": "AMMO_MG",
    "gxtName": "WT_MG_CBT",
    "gxtDescription": "WTD_MG_CBT",
    "components": [
      {
        "nameHash": "COMPONENT_COMBATMG_CLIP_01",
        "hash": -503336118,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_CLIP_02",
        "hash": -691692330,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM",
        "hash": -1596416958,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_VARMOD_LOWRIDER",
        "hash": -1828795171,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PUMPSHOTGUN",
    "hash": 487013001,
    "clipSize": 8,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_pumpshotgun",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_SG_PMP",
    "gxtDescription": "WTD_SG_PMP",
    "components": [
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_CLIP_01",
        "hash": -781249480,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SR_SUPP",
        "hash": -435637410,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_VARMOD_LOWRIDER",
        "hash": -1562927653,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SAWNOFFSHOTGUN",
    "hash": 2017895192,
    "clipSize": 8,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_sawnoff",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_SG_SOF",
    "gxtDescription": "WTD_SG_SOF",
    "components": [
      {
        "nameHash": "COMPONENT_SAWNOFFSHOTGUN_CLIP_01",
        "hash": -942267867,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SAWNOFFSHOTGUN_VARMOD_LUXE",
        "hash": -2052698631,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_ASSAULTSHOTGUN",
    "hash": -494615257,
    "clipSize": 8,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_assaultshotgun",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_SG_ASL",
    "gxtDescription": "WTD_SG_ASL",
    "components": [
      {
        "nameHash": "COMPONENT_ASSAULTSHOTGUN_CLIP_01",
        "hash": -1796727865,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTSHOTGUN_CLIP_02",
        "hash": -2034401422,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_BULLPUPSHOTGUN",
    "hash": -1654528753,
    "clipSize": 14,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_bullpupshotgun",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_SG_BLP",
    "gxtDescription": "WTD_SG_BLP",
    "components": [
      {
        "nameHash": "COMPONENT_BULLPUPSHOTGUN_CLIP_01",
        "hash": -917613298,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_STUNGUN",
    "hash": 911657153,
    "clipSize": 2104529083,
    "group": "GROUP_STUNGUN",
    "model": "w_pi_stungun",
    "ammo": "AMMO_STUNGUN",
    "gxtName": "WT_STUN",
    "gxtDescription": "WTD_STUN",
    "components": []
  },
  {
    "nameHash": "WEAPON_SNIPERRIFLE",
    "hash": 100416529,
    "clipSize": 10,
    "group": "GROUP_SNIPER",
    "model": "w_sr_sniperrifle",
    "ammo": "AMMO_SNIPER",
    "gxtName": "WT_SNIP_RIF",
    "gxtDescription": "WTD_SNIP_RIF",
    "components": [
      {
        "nameHash": "COMPONENT_SNIPERRIFLE_CLIP_01",
        "hash": -1681506167,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_LARGE",
        "hash": -767279652,
        "isDefault": true,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MAX",
        "hash": -1135289737,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_SNIPERRIFLE_VARMOD_LUXE",
        "hash": 1077065191,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HEAVYSNIPER",
    "hash": 205991906,
    "clipSize": 6,
    "group": "GROUP_SNIPER",
    "model": "w_sr_heavysniper",
    "ammo": "AMMO_SNIPER",
    "gxtName": "WT_SNIP_HVY",
    "gxtDescription": "WTD_SNIP_HVY",
    "components": [
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_CLIP_01",
        "hash": 1198478068,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_LARGE",
        "hash": -767279652,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MAX",
        "hash": -1135289737,
        "isDefault": true,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_GUNRUN_MK2_UPGRADE",
        "hash": 1623028892,
        "isDefault": false,
        "attachBone": "gun_gripr"
      }
    ]
  },
  {
    "nameHash": "WEAPON_REMOTESNIPER",
    "hash": 856002082,
    "clipSize": 10,
    "group": "",
    "model": "",
    "ammo": "AMMO_SNIPER_REMOTE",
    "gxtName": "WT_SNIP_RMT",
    "gxtDescription": "WTD_SNIP_RMT",
    "components": []
  },
  {
    "nameHash": "WEAPON_GRENADELAUNCHER",
    "hash": -1568386805,
    "clipSize": 10,
    "group": "GROUP_HEAVY",
    "model": "w_lr_grenadelauncher",
    "ammo": "AMMO_GRENADELAUNCHER",
    "gxtName": "WT_GL",
    "gxtDescription": "WTD_GL",
    "components": [
      {
        "nameHash": "COMPONENT_GRENADELAUNCHER_CLIP_01",
        "hash": 296639639,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL",
        "hash": -1439939148,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_GRENADELAUNCHER_SMOKE",
    "hash": 1305664598,
    "clipSize": 10,
    "group": "GROUP_HEAVY",
    "model": "w_lr_grenadelauncher",
    "ammo": "AMMO_GRENADELAUNCHER_SMOKE",
    "gxtName": "WT_GL_SMOKE",
    "gxtDescription": "WTD_GL_SMOKE",
    "components": [
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL",
        "hash": -1439939148,
        "isDefault": false,
        "attachBone": "WAPScop"
      }
    ]
  },
  {
    "nameHash": "WEAPON_RPG",
    "hash": -1312131151,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_rpg",
    "ammo": "AMMO_RPG",
    "gxtName": "WT_RPG",
    "gxtDescription": "WTD_RPG",
    "components": [
      {
        "nameHash": "COMPONENT_RPG_CLIP_01",
        "hash": 1319465907,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PASSENGER_ROCKET",
    "hash": 375527679,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_rpg",
    "ammo": "AMMO_RPG",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": [
      {
        "nameHash": "COMPONENT_RPG_CLIP_01",
        "hash": 1319465907,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_AIRSTRIKE_ROCKET",
    "hash": 324506233,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_rpg",
    "ammo": "AMMO_RPG",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": [
      {
        "nameHash": "COMPONENT_RPG_CLIP_01",
        "hash": 1319465907,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_STINGER",
    "hash": 1752584910,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_rpg",
    "ammo": "AMMO_STINGER",
    "gxtName": "WT_RPG",
    "gxtDescription": "WTD_RPG",
    "components": [
      {
        "nameHash": "COMPONENT_RPG_CLIP_01",
        "hash": 1319465907,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MINIGUN",
    "hash": 1119849093,
    "clipSize": 15000,
    "group": "GROUP_HEAVY",
    "model": "w_mg_minigun",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_MINIGUN",
    "gxtDescription": "WTD_MINIGUN",
    "components": [
      {
        "nameHash": "COMPONENT_MINIGUN_CLIP_01",
        "hash": -924946682,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_GRENADE",
    "hash": -1813897027,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_grenadefrag",
    "ammo": "AMMO_GRENADE",
    "gxtName": "WT_GNADE",
    "gxtDescription": "WTD_GNADE",
    "components": []
  },
  {
    "nameHash": "WEAPON_STICKYBOMB",
    "hash": 741814745,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_pe",
    "ammo": "AMMO_STICKYBOMB",
    "gxtName": "WT_GNADE_STK",
    "gxtDescription": "WTD_GNADE_STK",
    "components": []
  },
  {
    "nameHash": "WEAPON_SMOKEGRENADE",
    "hash": -37975472,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_grenadesmoke",
    "ammo": "AMMO_SMOKEGRENADE",
    "gxtName": "WT_GNADE_SMK",
    "gxtDescription": "WTD_GNADE_SMK",
    "components": []
  },
  {
    "nameHash": "WEAPON_BZGAS",
    "hash": -1600701090,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_grenadesmoke",
    "ammo": "AMMO_BZGAS",
    "gxtName": "WT_BZGAS",
    "gxtDescription": "WTD_BZGAS",
    "components": []
  },
  {
    "nameHash": "WEAPON_MOLOTOV",
    "hash": 615608432,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_molotov",
    "ammo": "AMMO_MOLOTOV",
    "gxtName": "WT_MOLOTOV",
    "gxtDescription": "WTD_MOLOTOV",
    "components": []
  },
  {
    "nameHash": "WEAPON_FIREEXTINGUISHER",
    "hash": 101631238,
    "clipSize": 2000,
    "group": "GROUP_FIREEXTINGUISHER",
    "model": "w_am_fire_exting",
    "ammo": "AMMO_FIREEXTINGUISHER",
    "gxtName": "WT_FIRE",
    "gxtDescription": "WTD_FIRE",
    "components": []
  },
  {
    "nameHash": "WEAPON_PETROLCAN",
    "hash": 883325847,
    "clipSize": 4500,
    "group": "GROUP_PETROLCAN",
    "model": "w_am_jerrycan",
    "ammo": "AMMO_PETROLCAN",
    "gxtName": "WT_PETROL",
    "gxtDescription": "WTD_PETROL",
    "components": []
  },
  {
    "nameHash": "WEAPON_DIGISCANNER",
    "hash": -38085395,
    "clipSize": 17,
    "group": "GROUP_DIGISCANNER",
    "model": "w_am_digiscanner",
    "ammo": "NULL",
    "gxtName": "WT_DIGI",
    "gxtDescription": "WTD_DIGI",
    "components": []
  },
  {
    "nameHash": "GADGET_NIGHTVISION",
    "hash": -1491061156,
    "clipSize": 0,
    "group": "GROUP_NIGHTVISION",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_NV",
    "gxtDescription": "WTD_NV",
    "components": []
  },
  {
    "nameHash": "GADGET_PARACHUTE",
    "hash": -72657034,
    "clipSize": 0,
    "group": "GROUP_PARACHUTE",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_PARA",
    "gxtDescription": "WTD_PARA",
    "components": []
  },
  {
    "nameHash": "OBJECT",
    "hash": 966099553,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": [
      {
        "nameHash": "POLICE_TORCH_FLASHLIGHT",
        "hash": -979169299,
        "isDefault": false,
        "attachBone": "Torch_Bulb"
      }
    ]
  },
  {
    "nameHash": "WEAPON_BRIEFCASE",
    "hash": -2000187721,
    "clipSize": 0,
    "group": "",
    "model": "w_am_case",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_BRIEFCASE_02",
    "hash": 28811031,
    "clipSize": 0,
    "group": "",
    "model": "w_am_brfcase",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_BALL",
    "hash": 600439132,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_am_baseball",
    "ammo": "AMMO_BALL",
    "gxtName": "WT_BALL",
    "gxtDescription": "WTD_BALL",
    "components": []
  },
  {
    "nameHash": "WEAPON_FLARE",
    "hash": 1233104067,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_am_flare",
    "ammo": "AMMO_FLARE",
    "gxtName": "WT_FLARE",
    "gxtDescription": "WTD_FLARE",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TANK",
    "hash": 1945616459,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_TANK",
    "gxtName": "WT_V_TANK",
    "gxtDescription": "WTD_V_TANK",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SPACE_ROCKET",
    "hash": -123497569,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_SPACE_ROCKET",
    "gxtName": "WT_V_PLANEMSL",
    "gxtDescription": "WTD_V_PLANEMSL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLANE_ROCKET",
    "hash": -821520672,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_PLANE_ROCKET",
    "gxtName": "WT_V_PLANEMSL",
    "gxtDescription": "WTD_V_PLANEMSL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_LASER",
    "hash": -268631733,
    "clipSize": 100,
    "group": "",
    "model": "",
    "ammo": "AMMO_PLAYER_LASER",
    "gxtName": "WT_V_PLRLSR",
    "gxtDescription": "WTD_V_PLRLSR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_BULLET",
    "hash": 1259576109,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_BUZZARD",
    "hash": 1186503822,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_HUNTER",
    "hash": -1625648674,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_LAZER",
    "hash": -494786007,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ENEMY_LASER",
    "hash": 1566990507,
    "clipSize": 100,
    "group": "",
    "model": "",
    "ammo": "AMMO_ENEMY_LASER",
    "gxtName": "WT_A_ENMYLSR",
    "gxtDescription": "WTD_A_ENMYLSR",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_SEARCHLIGHT",
    "hash": -844344963,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_RADAR",
    "hash": -764006018,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_VEHICLE_ROCKET",
    "hash": -1090665087,
    "clipSize": 1,
    "group": "GROUP_HEAVY",
    "model": "w_lr_rpg",
    "ammo": "AMMO_RPG",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": [
      {
        "nameHash": "COMPONENT_RPG_CLIP_01",
        "hash": 1319465907,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_BARBED_WIRE",
    "hash": 1223143800,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_DROWNING",
    "hash": -10959621,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_DROWNING_IN_VEHICLE",
    "hash": 1936677264,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_BLEEDING",
    "hash": -1955384325,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_ELECTRIC_FENCE",
    "hash": -1833087301,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_ELCFEN",
    "gxtDescription": "WTD_ELCFEN",
    "components": []
  },
  {
    "nameHash": "WEAPON_EXPLOSION",
    "hash": 539292904,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_FALL",
    "hash": -842959696,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_EXHAUSTION",
    "hash": 910830060,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_HIT_BY_WATER_CANNON",
    "hash": -868994466,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_RAMMED_BY_CAR",
    "hash": 133987706,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_RUN_OVER_BY_CAR",
    "hash": -1553120962,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_HELI_CRASH",
    "hash": 341774354,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_ROTORS",
    "hash": -1323279794,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_FIRE",
    "hash": -544306709,
    "clipSize": 0,
    "group": "",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_ANIMAL_RETRIEVER",
    "hash": -440934790,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_SMALL_DOG",
    "hash": -1148198339,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_TIGER_SHARK",
    "hash": 743550225,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_HAMMERHEAD_SHARK",
    "hash": -1263987253,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_KILLER_WHALE",
    "hash": -96609051,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_BOAR",
    "hash": 861723357,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_PIG",
    "hash": 1205296881,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_COYOTE",
    "hash": 1161062353,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_DEER",
    "hash": -188319074,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_HEN",
    "hash": 955837630,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_RABBIT",
    "hash": -1501041657,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_CAT",
    "hash": -495648874,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_COW",
    "hash": 94548753,
    "clipSize": 0,
    "group": "GROUP_UNARMED",
    "model": "",
    "ammo": "NULL",
    "gxtName": "WT_INVALID",
    "gxtDescription": "WTD_INVALID",
    "components": []
  },
  {
    "nameHash": "WEAPON_BIRD_CRAP",
    "hash": 1834887169,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_birdshat",
    "ammo": "AMMO_BIRD_CRAP",
    "gxtName": "WT_GNADE",
    "gxtDescription": "WTD_GNADE",
    "components": []
  },
  {
    "nameHash": "WEAPON_SNOWBALL",
    "hash": 126349499,
    "clipSize": 1,
    "group": "GROUP_THROWN",
    "model": "w_ex_snowball",
    "ammo": "AMMO_SNOWBALL",
    "gxtName": "WT_SNWBALL",
    "gxtDescription": "WTD_SNWBALL",
    "components": []
  },
  {
    "nameHash": "WEAPON_SNSPISTOL",
    "hash": -1076751822,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_sns_pistol",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_SNSPISTOL",
    "gxtDescription": "WTD_SNSPISTOL",
    "components": [
      {
        "nameHash": "COMPONENT_SNSPISTOL_CLIP_01",
        "hash": -125817127,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_CLIP_02",
        "hash": 2063610803,
        "isDefault": false,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SPECIALCARBINE",
    "hash": -1063057011,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_specialcarbine",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_SPCARBINE",
    "gxtDescription": "WTD_SPCARBINE",
    "components": [
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_CLIP_01",
        "hash": -959978111,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_CLIP_02",
        "hash": 2089537806,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM",
        "hash": -1596416958,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP",
        "hash": 202788691,
        "isDefault": false,
        "attachBone": "WAPGrip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_STONE_HATCHET",
    "hash": 940833800,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_stonehatchet",
    "ammo": "NULL",
    "gxtName": "WT_SHATCHET",
    "gxtDescription": "WTD_SHATCHET",
    "components": []
  },
  {
    "nameHash": "WEAPON_SWITCHBLADE",
    "hash": -538741184,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_switchblade",
    "ammo": "NULL",
    "gxtName": "WT_SWBLADE",
    "gxtDescription": "WTD_SWBLADE",
    "components": [
      {
        "nameHash": "COMPONENT_SWITCHBLADE_VARMOD_BASE",
        "hash": -1858624256,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SWITCHBLADE_VARMOD_VAR1",
        "hash": 1530822070,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SWITCHBLADE_VARMOD_VAR2",
        "hash": -409758110,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_ARENA_MACHINE_GUN",
    "hash": 889061222,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "WEAPON_ARENA_HOMING_MISSILE",
    "hash": 1686798800,
    "clipSize": 1,
    "group": "",
    "model": "",
    "ammo": "AMMO_ARENA_HOMING_MISSILE",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "WEAPON_ASSAULTRIFLE_MK2",
    "hash": 961495388,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_assaultriflemk2",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_RIFLE_ASL2",
    "gxtDescription": "WTD_RIFLE_ASL2",
    "components": [
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_01",
        "hash": -2045758401,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_02",
        "hash": -785724817,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_ARMORPIERCING",
        "hash": -1478681000,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_FMJ",
        "hash": 1675665560,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_INCENDIARY",
        "hash": -76490669,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CLIP_TRACER",
        "hash": -282298175,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_MK2",
        "hash": 77277509,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM_MK2",
        "hash": -966040254,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_BARREL_01",
        "hash": 1134861606,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_AR_BARREL_02",
        "hash": 1447477866,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO",
        "hash": -1860492113,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_02",
        "hash": 937772107,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_03",
        "hash": 1401650071,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_04",
        "hash": 628662130,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_05",
        "hash": -985047251,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_06",
        "hash": -812944463,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_07",
        "hash": -1447352303,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_08",
        "hash": -60338860,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_09",
        "hash": 2088750491,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_10",
        "hash": -1513913454,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_ASSAULTRIFLE_MK2_CAMO_IND_01",
        "hash": -1179558480,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_BULLPUPRIFLE_MK2",
    "hash": -2066285827,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_bullpupriflemk2",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_BULLRIFLE2",
    "gxtDescription": "WTD_BULLRIFLE2",
    "components": [
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_01",
        "hash": 25766362,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_02",
        "hash": -273676760,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_TRACER",
        "hash": -2111807319,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_INCENDIARY",
        "hash": -1449330342,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_ARMORPIERCING",
        "hash": -89655827,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CLIP_FMJ",
        "hash": 1130501904,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_02_MK2",
        "hash": -944910075,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL_MK2",
        "hash": 1060929921,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_BP_BARREL_01",
        "hash": 1704640795,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_BP_BARREL_02",
        "hash": 1005743559,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO",
        "hash": -1371515465,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_02",
        "hash": -1190793877,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_03",
        "hash": -1497085720,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_04",
        "hash": -1803148180,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_05",
        "hash": -1975971886,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_06",
        "hash": 36929477,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_07",
        "hash": -268444834,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_08",
        "hash": -574769446,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_09",
        "hash": -882699739,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_10",
        "hash": -1468181474,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_BULLPUPRIFLE_MK2_CAMO_IND_01",
        "hash": -974541230,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_CARBINERIFLE_MK2",
    "hash": -86904375,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_carbineriflemk2",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_RIFLE_CBN2",
    "gxtDescription": "WTD_RIFLE_CBN2",
    "components": [
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_01",
        "hash": 1283078430,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_02",
        "hash": 1574296533,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_ARMORPIERCING",
        "hash": 626875735,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_FMJ",
        "hash": 1141059345,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_INCENDIARY",
        "hash": 1025884839,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CLIP_TRACER",
        "hash": 391640422,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_MK2",
        "hash": 77277509,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM_MK2",
        "hash": -966040254,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      },
      {
        "nameHash": "COMPONENT_AT_CR_BARREL_01",
        "hash": -2093598721,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_CR_BARREL_02",
        "hash": -1958983669,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO",
        "hash": 1272803094,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_02",
        "hash": 1080719624,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_03",
        "hash": 792221348,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_04",
        "hash": -452181427,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_05",
        "hash": -746774737,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_06",
        "hash": -2044296061,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_07",
        "hash": -199171978,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_08",
        "hash": -1428075016,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_09",
        "hash": -1735153315,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_10",
        "hash": 1796459838,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_CARBINERIFLE_MK2_CAMO_IND_01",
        "hash": -631911105,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_COMBATMG_MK2",
    "hash": -608341376,
    "clipSize": 100,
    "group": "GROUP_MG",
    "model": "w_mg_combatmgmk2",
    "ammo": "AMMO_MG",
    "gxtName": "WT_MG_CBT2",
    "gxtDescription": "WTD_MG_CBT2",
    "components": [
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_01",
        "hash": 1227564412,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_02",
        "hash": 400507625,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_ARMORPIERCING",
        "hash": 696788003,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_FMJ",
        "hash": 1475288264,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_INCENDIARY",
        "hash": -1020871238,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CLIP_TRACER",
        "hash": -161179835,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL_MK2",
        "hash": 1060929921,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM_MK2",
        "hash": -966040254,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      },
      {
        "nameHash": "COMPONENT_AT_MG_BARREL_01",
        "hash": -1018236364,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_MG_BARREL_02",
        "hash": -1243457701,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO",
        "hash": 1249283253,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_02",
        "hash": -857707587,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_03",
        "hash": -1097543898,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_04",
        "hash": 1980349969,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_05",
        "hash": 1219453777,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_06",
        "hash": -1853459190,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_07",
        "hash": -2074781016,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_08",
        "hash": 457967755,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_09",
        "hash": 235171324,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_10",
        "hash": 42685294,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_COMBATMG_MK2_CAMO_IND_01",
        "hash": -687617715,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_DOUBLEACTION",
    "hash": -1746263880,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_wep1_gun",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_REV_DA",
    "gxtDescription": "WTD_REV_DA",
    "components": [
      {
        "nameHash": "COMPONENT_DOUBLEACTION_CLIP_01",
        "hash": 1328622785,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HEAVYSNIPER_MK2",
    "hash": 177293209,
    "clipSize": 6,
    "group": "GROUP_SNIPER",
    "model": "w_sr_heavysnipermk2",
    "ammo": "AMMO_SNIPER",
    "gxtName": "WT_SNIP_HVY2",
    "gxtDescription": "WTD_SNIP_HVY2",
    "components": [
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_01",
        "hash": -98690520,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_02",
        "hash": 752418717,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_ARMORPIERCING",
        "hash": -130689324,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_EXPLOSIVE",
        "hash": -1981031769,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_FMJ",
        "hash": 1005144310,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CLIP_INCENDIARY",
        "hash": 247526935,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_LARGE_MK2",
        "hash": -2101279869,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MAX",
        "hash": -1135289737,
        "isDefault": true,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_NV",
        "hash": -1233121104,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_THERMAL",
        "hash": 776198721,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SR_SUPP_03",
        "hash": -1404903567,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_08",
        "hash": 1602080333,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_09",
        "hash": 1764221345,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_SR_BARREL_01",
        "hash": -1869205321,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_SR_BARREL_02",
        "hash": 277524638,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO",
        "hash": -130843390,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_02",
        "hash": -977347227,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_03",
        "hash": -378461067,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_04",
        "hash": 329939175,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_05",
        "hash": 643374672,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_06",
        "hash": 807875052,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_07",
        "hash": -1401804168,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_08",
        "hash": -1096495395,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_09",
        "hash": -847811454,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_10",
        "hash": -1413108537,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_HEAVYSNIPER_MK2_CAMO_IND_01",
        "hash": 1815270123,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_MARKSMANRIFLE_MK2",
    "hash": 1785463520,
    "clipSize": 8,
    "group": "GROUP_SNIPER",
    "model": "w_sr_marksmanriflemk2",
    "ammo": "AMMO_SNIPER",
    "gxtName": "WT_MKRIFLE2",
    "gxtDescription": "WTD_MKRIFLE2",
    "components": [
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_01",
        "hash": -1797182002,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_02",
        "hash": -422587990,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_ARMORPIERCING",
        "hash": -193998727,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_FMJ",
        "hash": -515203373,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_INCENDIARY",
        "hash": 1842849902,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CLIP_TRACER",
        "hash": -679861550,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM_MK2",
        "hash": -966040254,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_LARGE_FIXED_ZOOM_MK2",
        "hash": 1528590652,
        "isDefault": true,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP",
        "hash": -2089531990,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      },
      {
        "nameHash": "COMPONENT_AT_MRFL_BARREL_01",
        "hash": 941317513,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_MRFL_BARREL_02",
        "hash": 1748450780,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO",
        "hash": -1869284448,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_02",
        "hash": 1931539634,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_03",
        "hash": 1624199183,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_04",
        "hash": -26834113,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_05",
        "hash": -210406055,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_06",
        "hash": 423313640,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_07",
        "hash": 276639596,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_08",
        "hash": -991356863,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_09",
        "hash": -1682848301,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_10",
        "hash": 996213771,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_MARKSMANRIFLE_MK2_CAMO_IND_01",
        "hash": -1214048550,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PISTOL_MK2",
    "hash": -1075685676,
    "clipSize": 12,
    "group": "GROUP_PISTOL",
    "model": "w_pi_pistolmk2",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_PIST2",
    "gxtDescription": "WTD_PIST2",
    "components": [
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_01",
        "hash": -1795936926,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_02",
        "hash": 1591132456,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_FMJ",
        "hash": 1329061674,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_HOLLOWPOINT",
        "hash": -2046910199,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_INCENDIARY",
        "hash": 733837882,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CLIP_TRACER",
        "hash": 634039983,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_RAIL",
        "hash": -1898661008,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH_02",
        "hash": 1140676955,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP_02",
        "hash": 1709866683,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_PI_COMP",
        "hash": 568543123,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_SLIDE",
        "hash": -1258515792,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_02_SLIDE",
        "hash": 438243936,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_03_SLIDE",
        "hash": -455079056,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_04_SLIDE",
        "hash": 740920107,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_05_SLIDE",
        "hash": -541616347,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_06_SLIDE",
        "hash": 1809261196,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_07_SLIDE",
        "hash": -1646538868,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_08_SLIDE",
        "hash": -1290164948,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_09_SLIDE",
        "hash": -964465134,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_10_SLIDE",
        "hash": 1135718771,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_IND_01_SLIDE",
        "hash": 1253942266,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO",
        "hash": 1550611612,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_02",
        "hash": 368550800,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_03",
        "hash": -1769069349,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_04",
        "hash": 24902297,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_05",
        "hash": -228041614,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_06",
        "hash": -584961562,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_07",
        "hash": -1153175946,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_08",
        "hash": 1301287696,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_09",
        "hash": 1597093459,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_10",
        "hash": 1769871776,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PISTOL_MK2_CAMO_IND_01",
        "hash": -1827882671,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_PUMPSHOTGUN_MK2",
    "hash": 1432025498,
    "clipSize": 8,
    "group": "GROUP_SHOTGUN",
    "model": "w_sg_pumpshotgunmk2",
    "ammo": "AMMO_SHOTGUN",
    "gxtName": "WT_SG_PMP2",
    "gxtDescription": "WTD_SG_PMP2",
    "components": [
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CLIP_01",
        "hash": -845938367,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CLIP_ARMORPIERCING",
        "hash": 1315288101,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CLIP_EXPLOSIVE",
        "hash": 1004815965,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CLIP_HOLLOWPOINT",
        "hash": -380098265,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CLIP_INCENDIARY",
        "hash": -1618338827,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_MK2",
        "hash": 77277509,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL_MK2",
        "hash": 1060929921,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_SR_SUPP_03",
        "hash": -1404903567,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_08",
        "hash": 1602080333,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO",
        "hash": -474112444,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_02",
        "hash": 387223451,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_03",
        "hash": 617753366,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_04",
        "hash": -222378256,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_05",
        "hash": 8741501,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_06",
        "hash": -601286203,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_07",
        "hash": -511433605,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_08",
        "hash": -655387818,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_09",
        "hash": -282476598,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_10",
        "hash": 1739501925,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_PUMPSHOTGUN_MK2_CAMO_IND_01",
        "hash": 1178671645,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_REVOLVER_MK2",
    "hash": -879347409,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_revolvermk2",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_REVOLVER2",
    "gxtDescription": "WTD_REVOLVER2",
    "components": [
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CLIP_01",
        "hash": -1172055874,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CLIP_FMJ",
        "hash": 231258687,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CLIP_HOLLOWPOINT",
        "hash": 284438159,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CLIP_INCENDIARY",
        "hash": 15712037,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CLIP_TRACER",
        "hash": -958864266,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_MK2",
        "hash": 77277509,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH",
        "hash": 899381934,
        "isDefault": false,
        "attachBone": "WAPFlshLasr"
      },
      {
        "nameHash": "COMPONENT_AT_PI_COMP_03",
        "hash": 654802123,
        "isDefault": false,
        "attachBone": "WAPSupp"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO",
        "hash": -1069552225,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_02",
        "hash": 11918884,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_03",
        "hash": 176157112,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_04",
        "hash": -220052855,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_05",
        "hash": 288456487,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_06",
        "hash": 398658626,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_07",
        "hash": 628697006,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_08",
        "hash": 925911836,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_09",
        "hash": 1222307441,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_10",
        "hash": 552442715,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_REVOLVER_MK2_CAMO_IND_01",
        "hash": -648943513,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SMG_MK2",
    "hash": 2024373456,
    "clipSize": 30,
    "group": "GROUP_SMG",
    "model": "w_sb_smgmk2",
    "ammo": "AMMO_SMG",
    "gxtName": "WT_SMG2",
    "gxtDescription": "WTD_SMG2",
    "components": [
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_01",
        "hash": 1277460590,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_02",
        "hash": -1182573778,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_FMJ",
        "hash": 190476639,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_HOLLOWPOINT",
        "hash": 974903034,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_INCENDIARY",
        "hash": -644734235,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CLIP_TRACER",
        "hash": 2146055916,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS_SMG",
        "hash": -1613015470,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_02_SMG_MK2",
        "hash": -452809877,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_SMALL_SMG_MK2",
        "hash": 1038927834,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_SB_BARREL_01",
        "hash": -653246751,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_SB_BARREL_02",
        "hash": -1520117877,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO",
        "hash": -996700057,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_02",
        "hash": 940943685,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_03",
        "hash": 1263226800,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_04",
        "hash": -328035840,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_05",
        "hash": 1224100642,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_06",
        "hash": 899228776,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_07",
        "hash": 616006309,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_08",
        "hash": -1561952511,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_09",
        "hash": 572063080,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_10",
        "hash": 1170588613,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SMG_MK2_CAMO_IND_01",
        "hash": 966612367,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SNSPISTOL_MK2",
    "hash": -2009644972,
    "clipSize": 6,
    "group": "GROUP_PISTOL",
    "model": "w_pi_sns_pistolmk2",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_SNSPISTOL2",
    "gxtDescription": "WTD_SNSPISTOL2",
    "components": [
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_01",
        "hash": 21392614,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_02",
        "hash": -829683854,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_TRACER",
        "hash": -1876057490,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_INCENDIARY",
        "hash": -424845447,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_HOLLOWPOINT",
        "hash": -1928301566,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CLIP_FMJ",
        "hash": -1055790298,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_FLSH_03",
        "hash": 1246324211,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_PI_RAIL_02",
        "hash": 1205768792,
        "isDefault": false,
        "attachBone": "WAPScop"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP_02",
        "hash": 1709866683,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_PI_COMP_02",
        "hash": -1434287169,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_SLIDE",
        "hash": -403805974,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_02_SLIDE",
        "hash": 691432737,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_03_SLIDE",
        "hash": 987648331,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_04_SLIDE",
        "hash": -431680535,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_05_SLIDE",
        "hash": -847582310,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_06_SLIDE",
        "hash": -92592218,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_07_SLIDE",
        "hash": -494548326,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_08_SLIDE",
        "hash": 730876697,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_09_SLIDE",
        "hash": 583159708,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_10_SLIDE",
        "hash": -1928503603,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_IND_01_SLIDE",
        "hash": 520557834,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO",
        "hash": 259780317,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_02",
        "hash": -1973342474,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_03",
        "hash": 1996130345,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_04",
        "hash": -1455657812,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_05",
        "hash": -1668263084,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_06",
        "hash": 1308243489,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_07",
        "hash": 1122574335,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_08",
        "hash": 1420313469,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_09",
        "hash": 109848390,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_10",
        "hash": 593945703,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SNSPISTOL_MK2_CAMO_IND_01",
        "hash": 1142457062,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_RAYPISTOL",
    "hash": -1355376991,
    "clipSize": 1,
    "group": "GROUP_PISTOL",
    "model": "w_pi_raygun",
    "ammo": "AMMO_RAYPISTOL",
    "gxtName": "WT_RAYPISTOL",
    "gxtDescription": "WTD_RAYPISTOL",
    "components": [
      {
        "nameHash": "COMPONENT_RAYPISTOL_VARMOD_XMAS18",
        "hash": -673450233,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "WEAPON_RAYCARBINE",
    "hash": 1198256469,
    "clipSize": 9999,
    "group": "GROUP_MG",
    "model": "w_ar_srifle",
    "ammo": "AMMO_MG",
    "gxtName": "WT_RAYCARBINE",
    "gxtDescription": "WTD_RAYCARBINE",
    "components": []
  },
  {
    "nameHash": "WEAPON_RAYMINIGUN",
    "hash": -1238556825,
    "clipSize": 15000,
    "group": "GROUP_HEAVY",
    "model": "w_mg_sminigun",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_RAYMINIGUN",
    "gxtDescription": "WTD_RAYMINIGUN",
    "components": [
      {
        "nameHash": "COMPONENT_MINIGUN_CLIP_01",
        "hash": -924946682,
        "isDefault": true,
        "attachBone": "WAPClip"
      }
    ]
  },
  {
    "nameHash": "WEAPON_SPECIALCARBINE_MK2",
    "hash": -1768145561,
    "clipSize": 30,
    "group": "GROUP_RIFLE",
    "model": "w_ar_specialcarbinemk2",
    "ammo": "AMMO_RIFLE",
    "gxtName": "WT_SPCARBINE2",
    "gxtDescription": "WTD_SPCARBINE2",
    "components": [
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_01",
        "hash": 382112385,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_02",
        "hash": -568352468,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_TRACER",
        "hash": -2023373174,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_INCENDIARY",
        "hash": -570355066,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_ARMORPIERCING",
        "hash": 1362433589,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CLIP_FMJ",
        "hash": 1346235024,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_AR_FLSH",
        "hash": 2076495324,
        "isDefault": false,
        "attachBone": "WAPFlshLasr_2"
      },
      {
        "nameHash": "COMPONENT_AT_SIGHTS",
        "hash": 1108334355,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MACRO_MK2",
        "hash": 77277509,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_SCOPE_MEDIUM_MK2",
        "hash": -966040254,
        "isDefault": false,
        "attachBone": "WAPScop_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_SUPP_02",
        "hash": -1489156508,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_01",
        "hash": -1181482284,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_02",
        "hash": -932732805,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_03",
        "hash": -569259057,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_04",
        "hash": -326080308,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_05",
        "hash": 48731514,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_06",
        "hash": 880736428,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_MUZZLE_07",
        "hash": 1303784126,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      },
      {
        "nameHash": "COMPONENT_AT_AR_AFGRIP_02",
        "hash": -1654288262,
        "isDefault": false,
        "attachBone": "WAPGrip_2"
      },
      {
        "nameHash": "COMPONENT_AT_SC_BARREL_01",
        "hash": -415870039,
        "isDefault": true,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_AT_SC_BARREL_02",
        "hash": -109086661,
        "isDefault": false,
        "attachBone": "WAPBarrel"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO",
        "hash": -737430213,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_02",
        "hash": 1125852043,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_03",
        "hash": 886015732,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_04",
        "hash": -1262287139,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_05",
        "hash": -295208411,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_06",
        "hash": -544154504,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_07",
        "hash": 172765678,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_08",
        "hash": -1982877449,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_09",
        "hash": 2072122460,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_10",
        "hash": -1986220171,
        "isDefault": false,
        "attachBone": "gun_root"
      },
      {
        "nameHash": "COMPONENT_SPECIALCARBINE_MK2_CAMO_IND_01",
        "hash": 1377355801,
        "isDefault": false,
        "attachBone": "gun_root"
      }
    ]
  },
  {
    "nameHash": "VEHICLE_WEAPON_TURRET_BOXVILLE",
    "hash": -1253095144,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TURRET_INSURGENT",
    "hash": 1155224728,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TURRET_LIMO",
    "hash": 729375873,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TURRET_TECHNICAL",
    "hash": 2144528907,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MG",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE",
    "hash": 1097917585,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_PLRBUL",
    "gxtDescription": "WTD_V_PLRBUL",
    "components": []
  },
  {
    "nameHash": "VEHICLE_WEAPON_TURRET_VALKYRIE",
    "hash": -1538179531,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_TURRET",
    "gxtDescription": "WTD_V_TURRET",
    "components": []
  },
  {
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
  },
  {
    "nameHash": "VEHICLE_WEAPON_PLAYER_SAVAGE",
    "hash": 1638077257,
    "clipSize": 750,
    "group": "",
    "model": "",
    "ammo": "AMMO_MINIGUN",
    "gxtName": "WT_V_LZRCAN",
    "gxtDescription": "WTD_V_LZRCAN",
    "components": []
  },
  {
    "nameHash": "WEAPON_VINTAGEPISTOL",
    "hash": 137902532,
    "clipSize": 7,
    "group": "GROUP_PISTOL",
    "model": "w_pi_vintage_pistol",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_VPISTOL",
    "gxtDescription": "WTD_VPISTOL",
    "components": [
      {
        "nameHash": "COMPONENT_VINTAGEPISTOL_CLIP_01",
        "hash": 1168357051,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_VINTAGEPISTOL_CLIP_02",
        "hash": 867832552,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_AT_PI_SUPP",
        "hash": -1023114086,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_WRENCH",
    "hash": 419712736,
    "clipSize": 0,
    "group": "GROUP_MELEE",
    "model": "w_me_wrench",
    "ammo": "NULL",
    "gxtName": "WT_WRENCH",
    "gxtDescription": "WTD_WRENCH",
    "components": []
  },
  {
    "nameHash": "WEAPON_CERAMICPISTOL",
    "hash": 727643628,
    "clipSize": 12,
    "group": "GROUP_PISTOL",
    "model": "w_pi_ceramic_pistol",
    "ammo": "AMMO_PISTOL",
    "gxtName": "WT_CERPST",
    "gxtDescription": "WTD_CERPST",
    "components": [
      {
        "nameHash": "COMPONENT_CERAMICPISTOL_CLIP_01",
        "hash": 1423184737,
        "isDefault": true,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CERAMICPISTOL_CLIP_02",
        "hash": -2122814295,
        "isDefault": false,
        "attachBone": "WAPClip"
      },
      {
        "nameHash": "COMPONENT_CERAMICPISTOL_SUPP",
        "hash": -1828202758,
        "isDefault": false,
        "attachBone": "WAPSupp_2"
      }
    ]
  },
  {
    "nameHash": "WEAPON_HAZARDCAN",
    "hash": -1168940174,
    "clipSize": 4500,
    "group": "GROUP_PETROLCAN",
    "model": "w_ch_jerrycan",
    "ammo": "AMMO_HAZARDCAN",
    "gxtName": "WT_HAZARDCAN",
    "gxtDescription": "WTD_HAZARDCAN",
    "components": []
  },
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
  },
  {
    "nameHash": "WEAPON_TRANQUILIZER",
    "hash": 849905853,
    "clipSize": 2104529083,
    "group": "GROUP_TRANQILIZER",
    "model": "w_pi_stungun",
    "ammo": "AMMO_TRANQUILIZER",
    "gxtName": "WT_STUN",
    "gxtDescription": "WTD_STUN",
    "components": []
  }
])"};
    Json loaded(loads(test_json));
    dump(loaded, "~/1.json");
    std::cout << loaded << std::endl;
    return 0;
}
