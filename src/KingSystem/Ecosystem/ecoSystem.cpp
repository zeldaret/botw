#include "KingSystem/Ecosystem/ecoSystem.h"

namespace ksys::eco {

static const char* sStatusEffectNames[22] = {"StatusEffect",
                                             "LifeRecover",
                                             "LifeMaxUp",
                                             "GutsPerformance",
                                             "ResistHot",
                                             "ResistCold",
                                             "ResistElectric",
                                             "MovingSpeed",
                                             "SwimingSpeed",
                                             "SwimingAnimRate",
                                             "ClimbingSpeed",
                                             "AttackUp",
                                             "DefenseUp",
                                             "Quietness",
                                             "DesertMovingSpeed",
                                             "ThrowingPower",
                                             "SnowMovingSpeed",
                                             "GutsRecoverSpeed",
                                             "ResistThunder",
                                             "ArmorChargeAttackAddLevel",
                                             "ReduceAncientEnemyDamge",
                                             "MaterSwordAttackUp"};

SEAD_SINGLETON_DISPOSER_IMPL(Ecosystem)

void Ecosystem::calc() {}

// NON_MATCHING: FP instructions rearranged.
s32 Ecosystem::getMapArea(const EcoMapInfo& info, f32 posX, f32 posZ) const {
    posX = sead::clamp(posX, -5000.0F, 4999.0F);
    posZ = sead::clamp(posZ, -4000.0F, 4000.0F);
    f32 epsilon1 = (posX + 5000.0F >= 0.0F) ? 0.5F : -0.5F;
    f32 epsilon2 = (posZ + 4000.0F >= 0.0F) ? 0.5F : -0.5F;
    s32 x = posX + 5000.0F + epsilon1;
    s32 z = (posZ + 4000.0F + epsilon2) / info.mHeader->divisor;

    s32 row = sead::clamp(z, (s32)0, info.mHeader->num_rows - 2);

    if (info.mHeader->divisor == 10)
        x = x / 10;

    s32* offsets = (s32*)info.mRowOffsets + row;
    s32 val0 = offsets[0];
    s32 val1 = offsets[1];

    if (val0 >= val1)
        return -1;

    Segment* segmentEnd = reinterpret_cast<Segment*>((char*)info.mRows + 2 * val1);
    Segment* segment = reinterpret_cast<Segment*>((char*)info.mRows + 2 * val0);
    s32 totalLength = 0;
    while (true) {
        totalLength += segment->length;
        if (x < totalLength)
            return segment->value;
        ++segment;
        if (segment >= segmentEnd)
            return -1;
    }
}

void Ecosystem::getAreaNameByNum(s32 areaNum, const char** out) const {
    *out = nullptr;

    if (areaNum < 0 || (s32)mAreaDataSize <= areaNum)
        return;

    al::ByamlIter iter;

    if (mAreaDataIter->tryGetIterByIndex(&iter, areaNum))
        iter.tryGetStringByKey(out, "Area");
}

// NON_MATCHING: Equivalent, minor conditional differences and register usage
void Ecosystem::getStatusEffectInfo(StatusEffect statusEffectIdx, s32 idx,
                                    eco::StatusEffectInfo* out) const {
    al::ByamlIter listIter;
    if (!mStatusEffectListIter->tryGetIterByIndex(&listIter, 0))
        return;

    al::ByamlIter iter;
    if (!listIter.tryGetIterByKey(&iter, sStatusEffectNames[statusEffectIdx])) {
        out->ng = true;
        out->val._s32 = 0;
        return;
    }

    bool special = false;
    al::ByamlIter result;
    if (iter.tryGetIterByIndex(&result, 0)) {
        result.tryGetBoolByKey(&special, "special");
        if (special) {
            out->ng = true;
            out->val._s32 = 0;
            return;
        }
    }

    al::ByamlIter result2;
    if (!iter.tryGetIterByIndex(&result2, 1))
        return;

    al::ByamlIter a1;
    result2.tryGetIterByIndex(&a1, 0);
    s32 numLevels = a1.getSize();
    if (numLevels > 0) {
        if (idx > numLevels - 1) {
            idx = numLevels - 1;
        }
    } else {
        out->ng = true;
        out->val._s32 = 0;
        return;
    }

    al::ByamlIter dict;
    if (!a1.tryGetIterByIndex(&dict, idx))
        return;

    f32 val = 0;
    s32 val2 = 0;

    if (dict.tryGetFloatByKey(&val, "val")) {
        out->ng = false;
        out->val._f32 = val;
        return;
    }

    if (dict.tryGetIntByKey(&val2, "val")) {
        out->ng = false;
        out->val._f32 = val2;
    }
}

void Ecosystem::getClimateNameByNum(s32 areaNum, const char** out) const {
    *out = nullptr;

    if (areaNum < 0 || (s32)mAreaDataSize <= areaNum)
        return;

    al::ByamlIter iter;

    if (mAreaDataIter->tryGetIterByIndex(&iter, areaNum))
        iter.tryGetStringByKey(out, "Climate");
}

void Ecosystem::getEnvSoundNameByNum(s32 areaNum, const char** out) const {
    *out = nullptr;

    if (areaNum < 0 || (s32)mAreaDataSize <= areaNum)
        return;

    al::ByamlIter iter;

    if (mAreaDataIter->tryGetIterByIndex(&iter, areaNum))
        iter.tryGetStringByKey(out, "EnvSound");
}

void Ecosystem::getEcoTraitsByNum(s32 areaNum, EcosystemTraits* out) const {
    out->idx = 0;

    if (areaNum < 0 || (s32)mAreaDataSize <= areaNum)
        return;

    al::ByamlIter areaIter;
    if (!mAreaDataIter->tryGetIterByIndex(&areaIter, areaNum))
        return;

    al::ByamlIter iter;
    if (!areaIter.tryGetIterByKey(&iter, "Procedural"))
        return;

    s32 size = iter.getSize();
    if (size < 0)
        return;

    for (s32 i = 0; i != size; ++i) {
        if (++out->idx > 3)
            out->idx = 0;

        EcoTraitGrp* grp = &out->grps[i];
        grp->terrain_material._int = -1;
        grp->vegetation._int = -1;
        grp->geology._int = -1;
        grp->defoliation._int = -1;

        iter.tryGetIntByKey(&grp->terrain_material._int, "terrain_material");
        iter.tryGetIntByKey(&grp->vegetation._int, "vegetation");
        iter.tryGetIntByKey(&grp->geology._int, "geology");
        iter.tryGetIntByKey(&grp->defoliation._int, "defoliation");
    }
}

}  // namespace ksys::eco
