#pragma once

#include <agl/utl/aglParameterObj.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

enum class GParamListObjType {
    System = 0x0,
    General = 0x1,
    Enemy = 0x2,
    EnemyLevel = 0x3,
    EnemyRace = 0x4,
    AttackInterval = 0x5,
    EnemyShown = 0x6,
    BindBone = 0x7,
    Attack = 0x8,
    WeaponCommon = 0x9,
    WeaponThrow = 0xA,
    Sandworm = 0xB,
    SmallSword = 0xC,
    Rod = 0xD,
    LargeSword = 0xE,
    Spear = 0xF,
    Shield = 0x10,
    Bow = 0x11,
    WeaponOption = 0x12,
    MasterSword = 0x13,
    GuardianMiniWeapon = 0x14,
    Player = 0x15,
    Camera = 0x16,
    Grab = 0x17,
    Armor = 0x18,
    ArmorEffect = 0x19,
    ArmorHead = 0x1A,
    ArmorUpper = 0x1B,
    ShiekerStone = 0x1C,
    SeriesArmor = 0x1D,
    Liftable = 0x1E,
    Item = 0x1F,
    Rupee = 0x20,
    Arrow = 0x21,
    Bullet = 0x22,
    CureItem = 0x23,
    CookSpice = 0x24,
    LumberjackTree = 0x25,
    Npc = 0x26,
    NpcEquipment = 0x27,
    Zora = 0x28,
    Traveler = 0x29,
    Prey = 0x2A,
    AnimalFollowOffset = 0x2B,
    ExtendedEntity = 0x2C,
    BindActor = 0x2D,
    EatTarget = 0x2E,
    AnimalUnit = 0x2F,
    Insect = 0x30,
    Fish = 0x31,
    Rope = 0x32,
    Horse = 0x33,
    HorseUnit = 0x34,
    HorseObject = 0x35,
    HorseRider = 0x36,
    HorseCreator = 0x37,
    GiantArmorSlot = 0x38,
    GiantArmor = 0x39,
    Guardian = 0x3A,
    MonsterShop = 0x3B,
    Swarm = 0x3C,
    GelEnemy = 0x3D,
    Nest = 0x3E,
    Wizzrobe = 0x3F,
    StalEnemy = 0x40,
    GuardianMini = 0x41,
    ClothReaction = 0x42,
    Global = 0x43,
    Beam = 0x44,
    AutoGen = 0x45,
    ChemicalType = 0x46,
    Golem = 0x47,
    HorseTargetedInfo = 0x48,
    WolfLink = 0x49,
    Event = 0x4A,
    GolemIK = 0x4B,
    PictureBook = 0x4C,
    AirWall = 0x4D,
    Motorcycle = 0x4E,
};
inline constexpr size_t NumGParamListObjTypes = 1 + 0x4E;

/// Base class for GeneralParamList parameter objects.
/// @bug This should have a virtual destructor...
class GParamListObject : public sead::hostio::Node {
public:
    virtual const char* getName() const = 0;

    agl::utl::ParameterObj& getObj() { return mObj; }

protected:
    agl::utl::ParameterObj mObj;
};
KSYS_CHECK_SIZE_NX150(GParamListObject, 0x38);

}  // namespace ksys::res
