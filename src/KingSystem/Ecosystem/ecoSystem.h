#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Ecosystem/ecoLevelSensor.h"

namespace al {
class ByamlIter;
}

namespace ksys::eco {

struct EcoMapHeader {
    /// File magic (0x00112233).
    u32 magic;
    s32 num_rows;
    s32 divisor;
    u32 reserved;
};
KSYS_CHECK_SIZE_NX150(EcoMapHeader, 0x10);

struct Segment {
    s16 value;
    s16 length;
};

class EcoMapInfo {
public:
    const EcoMapHeader* mHeader;
    const s32* mRowOffsets;
    const char* mRows;
};

enum class AreaItemType {
    Animal,
    Fish,
    Insect,
    Bird,
    Mushroom,
    Fruit,
    Mineral,
    Plant,
    Enemy,
    GrassCut,
    AutoCliffMaterial,
    AutoPlacementMaterial,
    RuinAutoPlacement,
    RainBonusMaterial,
};

struct AreaWeapon {
    /// Weapon name.
    const char* name;
    /// Probability of this weapon appearing (0 to 100).
    float prob;
};

struct AreaItem {
    /// Actor name.
    const char* name;
    /// Appearance weight.
    float num;
    /// Weapons carried by this actor (if this is an enemy).
    sead::SafeArray<AreaWeapon, 24> weapons;
    /// Number of valid entries in the `weapons` array.
    int num_weapons;
    /// Name of the set this item appears in. Typically used for small fruits like berries.
    const char* set;
    float radius;
};

struct AreaItemSet {
    sead::SafeArray<AreaItem, 32> items;
    /// Number of valid entries in the `items` array.
    int count;
};

union StatusEffectVal {
    f32 _f32;
    s32 _s32;
};

struct StatusEffectInfo {
    bool ng;
    StatusEffectVal val;
};

enum StatusEffect {
    StatusEffect_LifeRecover = 0x0,
    StatusEffect_LifeMaxUp = 0x1,
    StatusEffect_GutsPerformance = 0x2,
    StatusEffect_ResistHot = 0x3,
    StatusEffect_ResistCold = 0x4,
    StatusEffect_ResistElectric = 0x5,
    StatusEffect_MovingSpeed = 0x6,
    StatusEffect_SwimingSpeed = 0x7,
    StatusEffect_SwimingAnimRate = 0x8,
    StatusEffect_ClimbingSpeed = 0x9,
    StatusEffect_AttackUp = 0xA,
    StatusEffect_DefenseUp = 0xB,
    StatusEffect_Quietness = 0xC,
    StatusEffect_DesertMovingSpeed = 0xD,
    StatusEffect_ThrowingPower = 0xE,
    StatusEffect_SnowMovingSpeed = 0xF,
    StatusEffect_GutsRecoverSpeed = 0x10,
    StatusEffect_ResistThunder = 0x11,
    StatusEffect_ArmorChargeAttackAddLevel = 0x12,
    StatusEffect_ReduceAncientEnemyDamge = 0x13,
    StatusEffect_MaterSwordAttackUp = 0x14,
};

union EcoTrait {
    s32 _int;
    struct {
        u8 _b0;
        u8 _b1;
        u8 _b2;
        u8 _b3;
    };
};

struct EcoTraitGrp {
    EcoTrait terrain_material;
    EcoTrait vegetation;
    EcoTrait geology;
    EcoTrait defoliation;
};

struct EcosystemTraits {
    u32 idx;
    EcoTraitGrp grps[3];
};
KSYS_CHECK_SIZE_NX150(EcosystemTraits, 0x34);

class Ecosystem {
    SEAD_SINGLETON_DISPOSER(Ecosystem)
private:
    Ecosystem() = default;
    virtual ~Ecosystem();

public:
    void init(sead::Heap* heap);
    void calc();

    s32 getMapArea(const EcoMapInfo& info, f32 posX, f32 posZ) const;

    s32 getFieldMapArea(f32 x, f32 z) const { return getMapArea(mFieldMapArea, x, z); }

    void getAreaItems(s32 areaNum, AreaItemType type, AreaItemSet* out) const;
    void getStatusEffectInfo(StatusEffect statusEffectIdx, s32 idx, StatusEffectInfo* out) const;
    void getAreaNameByNum(s32 areaNum, const char** out) const;
    void getClimateNameByNum(s32 areaNum, const char** out) const;
    void getEnvSoundNameByNum(s32 areaNum, const char** out) const;
    void getEcoTraitsByNum(s32 areaNum, EcosystemTraits* out) const;

private:
    struct Handles {
        res::Handle mFieldMapArea;
        res::Handle mAreaData;
        res::Handle mMapTower;
        res::Handle mStatusEffectList;
        res::Handle mLoadBalancer;
    };
    Handles mHandles;

    al::ByamlIter* mAreaDataIter{};
    u32 mAreaDataSize{};
    al::ByamlIter* mStatusEffectListIter{};
    LevelSensor* mLevelSensor{};
    EcoMapInfo mFieldMapArea{};
    EcoMapInfo mMapTower{};
    EcoMapInfo mLoadBalancer{};
    u32 mFlags{};
    u32 mLast;
};

}  // namespace ksys::eco
