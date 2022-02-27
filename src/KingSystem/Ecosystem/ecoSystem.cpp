#include "KingSystem/Ecosystem/ecoSystem.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/Byaml/Byaml.h"

namespace ksys::eco {

constexpr const char* sAreaItemTypeStr[] = {
    "Animal",
    "Fish",
    "Insect",
    "Bird",
    "Mushroom",
    "Fruit",
    "Mineral",
    "Plant",
    "Enemy",
    "GrassCut",
    "AutoCliffMaterial",
    "AutoPlacementMaterial",
    "RuinAutoPlacement",
    "RainBonusMaterial",
};

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

static void setEcoMapInfo(EcoMapInfo& info, const u8* data) {
    info.mHeader = reinterpret_cast<const EcoMapHeader*>(data);
    info.mRowOffsets = reinterpret_cast<const s32*>(info.mHeader + 1);
    info.mRows =
        reinterpret_cast<const char*>(info.mRowOffsets) + sizeof(int) * info.mHeader->num_rows;
}

void Ecosystem::init(sead::Heap* heap) {
    res::LoadRequest req;
    req.mRequester = "Ecosystem";

    req._22 = false;
    mHandles.mFieldMapArea.load("Ecosystem/FieldMapArea.beco", &req);

    req._22 = true;
    mHandles.mAreaData.load("Ecosystem/AreaData.byml", &req);

    req._22 = false;
    mHandles.mMapTower.load("Ecosystem/MapTower.beco", &req);

    req._22 = false;
    mHandles.mStatusEffectList.load("Ecosystem/StatusEffectList.byml", &req);

    req._22 = false;
    mHandles.mLoadBalancer.load("Ecosystem/LoadBalancer.beco", &req);

    auto* field_map_area =
        sead::DynamicCast<sead::DirectResource>(mHandles.mFieldMapArea.getResource());
    setEcoMapInfo(mFieldMapArea, field_map_area->getRawData());

    auto* map_tower = sead::DynamicCast<sead::DirectResource>(mHandles.mMapTower.getResource());
    setEcoMapInfo(mMapTower, map_tower->getRawData());

    auto* load_balancer =
        sead::DynamicCast<sead::DirectResource>(mHandles.mLoadBalancer.getResource());
    setEcoMapInfo(mLoadBalancer, load_balancer->getRawData());

    auto* area_data = sead::DynamicCast<sead::DirectResource>(mHandles.mAreaData.getResource());
    mAreaDataIter = new (heap) al::ByamlIter(area_data->getRawData());
    mAreaDataSize = mAreaDataIter->getSize();

    auto* status_effect_list =
        sead::DynamicCast<sead::DirectResource>(mHandles.mStatusEffectList.getResource());
    mStatusEffectListIter = new (heap) al::ByamlIter(status_effect_list->getRawData());

    mLevelSensor = new (heap) LevelSensor;
    mLevelSensor->init(heap);
}

void Ecosystem::calc() {}

// NON_MATCHING: FP instructions rearranged.
s32 Ecosystem::getMapArea(const EcoMapInfo& info, f32 posX, f32 posZ) const {
    posX = sead::Mathf::clamp(posX, -5000.0f, 4999.0f);
    posZ = sead::Mathf::clamp(posZ, -4000.0f, 4000.0f);

    const auto epsilon = [](float n) { return n >= 0.0f ? 0.5f : -0.5f; };

    s32 x = s32(posX + 5000.0f + epsilon(posX + 5000.0f));
    s32 z = s32(posZ + 4000.0f + epsilon(posZ + 4000.0f)) / info.mHeader->divisor;
    s32 row = sead::Mathi::clamp(z, 0, info.mHeader->num_rows - 2);

    if (info.mHeader->divisor == 10)
        x /= 10;

    const int offset_begin = info.mRowOffsets[row];
    const int offset_end = info.mRowOffsets[row + 1];
    if (offset_begin >= offset_end)
        return -1;

    // Offsets to segments are divided by 2 and relative to the start of the row section.
    static constexpr int OffsetMultiplier = 2;
    auto* segmentEnd = reinterpret_cast<const Segment*>(info.mRows + OffsetMultiplier * offset_end);
    auto* segment = reinterpret_cast<const Segment*>(info.mRows + OffsetMultiplier * offset_begin);
    s32 totalLength = 0;
    while (true) {
        totalLength += segment->length;
        if (x < totalLength)
            break;
        ++segment;
        if (segment >= segmentEnd)
            return -1;
    }
    return segment->value;
}

void Ecosystem::getAreaItems(s32 areaNum, AreaItemType type, AreaItemSet* out) const {
    out->count = 0;

    if (areaNum < 0 || areaNum >= int(mAreaDataSize))
        return;

    al::ByamlIter area_iter;
    if (!mAreaDataIter->tryGetIterByIndex(&area_iter, areaNum))
        return;

    al::ByamlIter items_iter;
    if (!area_iter.tryGetIterByKey(&items_iter, sAreaItemTypeStr[u32(type)]))
        return;

    out->count = items_iter.getSize();

    for (int i = 0; i < out->count; ++i) {
        al::ByamlIter item_iter;
        if (!items_iter.tryGetIterByIndex(&item_iter, i))
            continue;

        auto& entry = out->items[i];

        item_iter.tryGetStringByKey(&entry.name, "name");
        item_iter.tryGetFloatByKey(&entry.num, "num");

        if (!item_iter.tryGetStringByKey(&entry.set, "set"))
            entry.set = nullptr;

        if (!item_iter.tryGetFloatByKey(&entry.radius, "radius"))
            entry.radius = 0.0;

        al::ByamlIter weapons_iter;
        if (item_iter.tryGetIterByKey(&weapons_iter, "weapons")) {
            // Fill in weapon information now.
            for (int w_idx = 0; w_idx < weapons_iter.getSize(); ++w_idx) {
                al::ByamlIter weapon_iter;
                if (!weapons_iter.tryGetIterByIndex(&weapon_iter, w_idx))
                    continue;

                auto& weapon = entry.weapons[w_idx];
                weapon_iter.tryGetStringByKey(&weapon.name, "name");
                if (!weapon_iter.tryGetFloatByKey(&weapon.prob, "prob")) {
                    // Try to get `prob` again, this time as an integer.
                    int prob;
                    if (weapon_iter.tryGetIntByKey(&prob, "prob"))
                        weapon.prob = prob;
                    else
                        weapon.prob = 100.0;
                }
            }
            entry.num_weapons = weapons_iter.getSize();
        } else {
            entry.num_weapons = 0;
        }
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

Ecosystem::~Ecosystem() = default;

}  // namespace ksys::eco
