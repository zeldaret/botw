#pragma once

#include "Game/AI/AI/aiItemRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonItemRoot : public ItemRoot {
    SEAD_RTTI_OVERRIDE(DragonItemRoot, ItemRoot)
public:
    explicit DragonItemRoot(const InitArg& arg);
    ~DragonItemRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mFlyStartTime_s{};
    // static_param at offset 0x58
    const int* mClearFlagTimeAtRunel_s{};
    // static_param at offset 0x60
    const float* mGravity_s{};
    // static_param at offset 0x68
    const float* mFlyStartHeightAtRunel_s{};
    // static_param at offset 0x70
    sead::SafeString mTailXLinkEventName_s{};
    // static_param at offset 0x80
    sead::SafeString mAuraXLinkEventName_s{};
    // static_param at offset 0x90
    sead::SafeString mFlyPrepareXinkEventName_s{};
    // static_param at offset 0xa0
    sead::SafeString mFlyStartXinkEventName_s{};
    // static_param at offset 0xb0
    sead::SafeString mHitGroundXLinkEventName_s{};
    // static_param at offset 0xc0
    sead::SafeString mLightShaftXLinkEventName_s{};
    // static_param at offset 0xd0
    sead::SafeString mActivateXlinkEventName_s{};
    // static_param at offset 0xe0
    sead::SafeString mDestroySwitchGameData_s{};
    // static_param at offset 0xf0
    sead::SafeString mClearFlagLabel_s{};
    // static_param at offset 0x100
    sead::SafeString mDropItemFlagLabel_s{};
    // map_unit_param at offset 0x110
    const sead::Vector3f* mTargetPosition_m{};
    // aitree_variable at offset 0x118
    bool* mIsInitFromCarryBox_a{};
    // aitree_variable at offset 0x120
    bool* mIsInsideObserverArea_a{};
};

}  // namespace uking::ai
