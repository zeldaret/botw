#pragma once

#include <basis/seadTypes.h>
#include <heap/seadDisposer.h>
#include <heap/seadExpHeap.h>
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Ecosystem/ecoLevelSensor.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::eco {

struct EcoMapHeader {
    u32 unknown;
    s32 num_rows;
    s32 divisor;
};
struct Segment {
    s16 value;
    s16 length;
};

class EcoMapInfo {
public:
    EcoMapHeader* mHeader;
    u32* mRowOffsets;
    char* mRows;
};

enum ActorType {};

struct ActorSpawnInfo;

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
    void init();
    void calc();

    s32 getMapArea(const EcoMapInfo& info, f32 posX, f32 posZ) const;

    s32 getFieldMapArea(f32 x, f32 z) const { return getMapArea(mFieldMapArea, x, z); }

    void getActorSpawnInfo(s32 areaNum, ActorType actorTypeIdx, ActorSpawnInfo* out) const;
    void getStatusEffectInfo(StatusEffect statusEffectIdx, s32 idx, StatusEffectInfo* out) const;
    void getAreaNameByNum(s32 areaNum, const char** out) const;
    void getClimateNameByNum(s32 areaNum, const char** out) const;
    void getEnvSoundNameByNum(s32 areaNum, const char** out) const;
    void getEcoTraitsByNum(s32 areaNum, EcosystemTraits* out) const;

private:
    res::Handle mFieldMapAreaFile;
    res::Handle mAreaDataFile;
    res::Handle mMapTowerFile;
    res::Handle mStatusEffectListFile;
    res::Handle mLoadBalancerFile;

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
