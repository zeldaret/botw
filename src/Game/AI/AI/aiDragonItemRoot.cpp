#include "Game/AI/AI/aiDragonItemRoot.h"
#include <math/seadVector.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::ai {

DragonItemRoot::DragonItemRoot(const InitArg& arg) : ItemRoot(arg) {}

DragonItemRoot::~DragonItemRoot() = default;

bool DragonItemRoot::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void DragonItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
}

void DragonItemRoot::leave_() {
    ItemRoot::leave_();
}

void DragonItemRoot::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFlyStartTime_s, "FlyStartTime");
    getStaticParam(&mClearFlagTimeAtRunel_s, "ClearFlagTimeAtRunel");
    getStaticParam(&mGravity_s, "Gravity");
    getStaticParam(&mFlyStartHeightAtRunel_s, "FlyStartHeightAtRunel");
    getStaticParam(&mTailXLinkEventName_s, "TailXLinkEventName");
    getStaticParam(&mAuraXLinkEventName_s, "AuraXLinkEventName");
    getStaticParam(&mFlyPrepareXinkEventName_s, "FlyPrepareXinkEventName");
    getStaticParam(&mFlyStartXinkEventName_s, "FlyStartXinkEventName");
    getStaticParam(&mHitGroundXLinkEventName_s, "HitGroundXLinkEventName");
    getStaticParam(&mLightShaftXLinkEventName_s, "LightShaftXLinkEventName");
    getStaticParam(&mActivateXlinkEventName_s, "ActivateXlinkEventName");
    getStaticParam(&mDestroySwitchGameData_s, "DestroySwitchGameData");
    getStaticParam(&mClearFlagLabel_s, "ClearFlagLabel");
    getStaticParam(&mDropItemFlagLabel_s, "DropItemFlagLabel");
    getMapUnitParam(&mTargetPosition_m, "TargetPosition");
    getAITreeVariable(&mIsInitFromCarryBox_a, "IsInitFromCarryBox");
    getAITreeVariable(&mIsInsideObserverArea_a, "IsInsideObserverArea");
}

inline float sqXYZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    sead::Vector3f diff = a;
    diff -= b;
    return diff.squaredLength();
}

// Swapped arguments in fadd for distance calcuation
#ifdef NON_MATCHING
bool getDragonItemDropPosition(sead::Vector3f* target_pos, const sead::Vector3f& current_pos) {
    auto* mgr = ksys::map::PlacementMgr::instance();
    const auto& results = mgr->mTraverseResults[1 - mgr->mTraverseResultIdx];

    sead::SafeArray<sead::Vector3f, 3> pos;
    pos.fill(sead::Vector3f::zero);

    bool ok = false;
    for (const auto& obj : results.dragon_item_drop_targets) {
        const sead::Vector3f& obj_pos = obj.getTranslate();
        if (!(obj_pos.y < current_pos.y)) {
            continue;
        }

        // Looks like an Insertion Sort
        for (int i = 0; i < pos.size(); i++) {
            bool closer = sqXYZDistance(obj_pos, current_pos) < sqXYZDistance(pos[i], current_pos);
            if (closer || pos[i] == sead::Vector3f(0, 0, 0)) {
                if (i > 0) {
                    pos[i - 1] = pos[i];
                }
                pos[i] = obj_pos;
                ok = true;
            }
        }
    }
    if (!ok) {
        return false;
    }
    int index = sead::GlobalRandom::instance()->getS32Range(0, 3);
    target_pos->e = pos[index].e;
    return true;
}
#endif

}  // namespace uking::ai
