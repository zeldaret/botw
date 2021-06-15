#!/usr/bin/env python3
# Generates actInfoCommon.h and actInfoCommon.cpp.
from typing import Any, List, Tuple
from pathlib import Path

# Section | Name | Type | Default value (optional)
PROPERTIES: List[Tuple[str, str, str, Any]] = [
    ("System", "IsGetItemSelf", "bool"),

    ("General", "Life", "int", 100),

    ("Enemy", "Rank", "int"),

    ("Attack", "Power", "int"),

    ("WeaponCommon", "GuardPower", "int"),
    ("WeaponCommon", "SharpWeaponPer", "float", 10.0),
    ("WeaponCommon", "SharpWeaponAddAtkMin", "int"),
    ("WeaponCommon", "SharpWeaponAddAtkMax", "int"),
    ("WeaponCommon", "SharpWeaponAddLifeMin", "int"),
    ("WeaponCommon", "SharpWeaponAddLifeMax", "int"),
    ("WeaponCommon", "SharpWeaponAddCrit", "bool"),
    ("WeaponCommon", "SharpWeaponAddGuardMin", "int"),
    ("WeaponCommon", "SharpWeaponAddGuardMax", "int"),

    ("WeaponCommon", "PoweredSharpAddAtkMin", "int"),
    ("WeaponCommon", "PoweredSharpAddAtkMax", "int"),
    ("WeaponCommon", "PoweredSharpAddLifeMin", "int"),
    ("WeaponCommon", "PoweredSharpAddLifeMax", "int"),
    ("WeaponCommon", "PoweredSharpWeaponAddGuardMin", "int"),
    ("WeaponCommon", "PoweredSharpWeaponAddGuardMax", "int"),
    ("WeaponCommon", "PoweredSharpAddThrowMin", "float", 1.0),
    ("WeaponCommon", "PoweredSharpAddThrowMax", "float", 1.0),
    ("WeaponCommon", "PoweredSharpAddSpreadFire", "bool"),
    ("WeaponCommon", "PoweredSharpAddZoomRapid", "bool"),
    ("WeaponCommon", "PoweredSharpAddRapidFireMin", "float", 1.0),
    ("WeaponCommon", "PoweredSharpAddRapidFireMax", "float", 1.0),
    ("WeaponCommon", "PoweredSharpAddSurfMaster", "bool"),

    ("Bow", "ArrowName", "const char*"),
    ("Bow", "IsLeadShot", "bool"),
    ("Bow", "LeadShotNum", "int"),
    ("Bow", "IsRapidFire", "bool"),
    ("Bow", "RapidFireNum", "int"),

    ("MasterSword", "TrueFormAttackPower", "int", -1),
    ("MasterSword", "SearchEvilDist", "float", -1.0),
    ("MasterSword", "SleepActorName", "const char*"),
    ("MasterSword", "TrueFormActorName", "const char*"),

    ("Armor", "StarNum", "int"),
    ("Armor", "DefenceAddLevel", "int"),
    ("Armor", "NextRankName", "const char*"),

    ("ArmorEffect", "EffectType", "const char*", "None"),
    ("ArmorEffect", "EffectLevel", "int"),
    ("ArmorEffect", "AncientPowUp", "bool"),
    ("ArmorEffect", "EnableClimbWaterfall", "bool"),
    ("ArmorEffect", "EnableSpinAttack", "bool"),

    ("ArmorHead", "MantleType", "int"),

    ("ArmorUpper", "DisableSelfMantle", "bool"),
    ("ArmorUpper", "UseMantleType", "int"),

    ("SeriesArmor", "SeriesType", "const char*"),

    ("Item", "SellingPrice", "int", -1),
    ("Item", "BuyingPrice", "int", -1),
    ("Item", "CreatingPrice", "int", -1),
    ("Item", "StainColor", "int", -1),
    ("Item", "SaleRevivalCount", "int", -1),
    ("Item", "UseIconActorName", "const char*"),

    ("Rupee", "RupeeValue", "int", 1),

    ("Arrow", "ArrowNum", "int"),
    ("Arrow", "EnemyShootNumForDelete", "int"),
    ("Arrow", "ArrowDeletePer", "int"),

    ("CureItem", "HitPointRecover", "int"),
    ("CureItem", "EffectiveTime", "int"),

    ("Traveler", "AppearGameDataName", "const char*"),
    ("Traveler", "DeleteGameDataName", "const char*"),
    ("Traveler", "RouteType", "const char*"),
    ("Traveler", "RideHorseName", "const char*"),
    ("Traveler", "RoutePoint0Name", "const char*"),
    ("Traveler", "RoutePoint1Name", "const char*"),
    ("Traveler", "RoutePoint2Name", "const char*"),
    ("Traveler", "RoutePoint3Name", "const char*"),
    ("Traveler", "RoutePoint4Name", "const char*"),
    ("Traveler", "RoutePoint5Name", "const char*"),
    ("Traveler", "RoutePoint6Name", "const char*"),
    ("Traveler", "RoutePoint7Name", "const char*"),
    ("Traveler", "RoutePoint8Name", "const char*"),
    ("Traveler", "RoutePoint9Name", "const char*"),
    ("Traveler", "RoutePoint10Name", "const char*"),
    ("Traveler", "RoutePoint11Name", "const char*"),
    ("Traveler", "RoutePoint12Name", "const char*"),
    ("Traveler", "RoutePoint13Name", "const char*"),
    ("Traveler", "RoutePoint14Name", "const char*"),
    ("Traveler", "RoutePoint15Name", "const char*"),
    ("Traveler", "RoutePoint16Name", "const char*"),
    ("Traveler", "RoutePoint17Name", "const char*"),
    ("Traveler", "RoutePoint18Name", "const char*"),
    ("Traveler", "RoutePoint19Name", "const char*"),
    ("Traveler", "RoutePoint20Name", "const char*"),
    ("Traveler", "RoutePoint21Name", "const char*"),
    ("Traveler", "RoutePoint22Name", "const char*"),
    ("Traveler", "RoutePoint23Name", "const char*"),
    ("Traveler", "RoutePoint24Name", "const char*"),
    ("Traveler", "RoutePoint25Name", "const char*"),
    ("Traveler", "RoutePoint26Name", "const char*"),
    ("Traveler", "RoutePoint27Name", "const char*"),
    ("Traveler", "RoutePoint28Name", "const char*"),
    ("Traveler", "RoutePoint29Name", "const char*"),

    ("Horse", "ASVariation", "const char*", "Normal"),
    ("Horse", "Nature", "int"),
    ("Horse", "GearTopChargeNum", "int", 3),

    ("HorseUnit", "RiddenAnimalType", "int"),

    ("MonsterShop", "BuyMamo", "int"),
    ("MonsterShop", "SellMamo", "int"),

    ("PictureBook", "LiveSpot1", "int", -1),
    ("PictureBook", "LiveSpot2", "int", -1),
    ("PictureBook", "SpecialDrop", "int", -1),
]


def generate_declarations(props: list) -> str:
    lines = []
    for prop in props:
        assert len(prop) == 3 or len(prop) == 4
        section, name, type_, *_ = prop
        lines.append(f"{type_} get{section}{name}(InfoData* data, const char* actor);")
        lines.append(f"{type_} get{section}{name}(const al::ByamlIter& iter);")
        lines.append("")
    return "\n".join(lines)


def get_key_name(section: str, name: str) -> str:
    return section[0].lower() + section[1:] + name


def generate_definitions(props: list) -> str:
    _getters = {
        "int": "getInt",
        "bool": "getBool",
        "float": "getFloat",
        "const char*": "getString",
    }

    lines = []
    for prop in props:
        assert len(prop) == 3 or len(prop) == 4
        if len(prop) == 3:
            section, name, type_ = prop
            key = get_key_name(section, name)

            lines.append(f"{type_} get{section}{name}(InfoData* data, const char* actor) {{")
            lines.append(f"    return data->{_getters[type_]}(actor, \"{key}\");")
            lines.append(f"}}")
            lines.append("")
            lines.append(f"{type_} get{section}{name}(const al::ByamlIter& iter) {{")
            lines.append(f"    return InfoData::{_getters[type_]}ByKey(iter, \"{key}\");")
            lines.append(f"}}")
            lines.append("")
        else:
            section, name, type_, default_ = prop
            key = get_key_name(section, name)
            default_str = f'"{default_}"' if isinstance(default_, str) else str(default_)

            lines.append(f"{type_} get{section}{name}(InfoData* data, const char* actor) {{")
            lines.append(f"    return data->{_getters[type_]}(actor, \"{key}\", {default_str});")
            lines.append(f"}}")
            lines.append("")
            lines.append(f"{type_} get{section}{name}(const al::ByamlIter& iter) {{")
            lines.append(f"    return InfoData::{_getters[type_]}ByKey(iter, \"{key}\", {str(default_str)});")
            lines.append(f"}}")
            lines.append("")

    return "\n".join(lines)


header_contents = """\
#pragma once

// DO NOT EDIT. This file is automatically generated by actInfoCommon.py.

namespace al {
class ByamlIter;
}

namespace ksys::act {

class InfoData;

""" + generate_declarations(PROPERTIES) + """\

}  // namespace ksys::act
"""

cpp_contents = """\
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"

// DO NOT EDIT. This file is automatically generated by actInfoCommon.py.

namespace ksys::act {

""" + generate_definitions(PROPERTIES) + """\

}  // namespace ksys::act
"""

this_dir = Path(__file__).parent
(this_dir / "actInfoCommon.h").write_text(header_contents)
(this_dir / "actInfoCommon.cpp").write_text(cpp_contents)
