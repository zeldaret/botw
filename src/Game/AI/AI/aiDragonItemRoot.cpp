#include "Game/AI/AI/aiDragonItemRoot.h"

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

}  // namespace uking::ai
