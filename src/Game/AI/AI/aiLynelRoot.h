#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(LynelRoot, EnemyRoot)
public:
    explicit LynelRoot(const InitArg& arg);
    ~LynelRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const int* mBowIdx_s{};
    // static_param at offset 0x1e0
    const float* mBoneStandAddRatio_s{};
    // static_param at offset 0x1e8
    sead::SafeString mRoarFlameActorName_s{};
    // static_param at offset 0x1f8
    sead::SafeString mRoarFlamePartsKey_s{};
    // static_param at offset 0x208
    sead::SafeString mBreathActorName_s{};
    // static_param at offset 0x218
    sead::SafeString mBreathPartsKey0_s{};
    // static_param at offset 0x228
    sead::SafeString mBreathPartsKey1_s{};
    // static_param at offset 0x238
    sead::SafeString mBreathPartsKey2_s{};
    // static_param at offset 0x248
    sead::SafeString mStandBoneName_s{};
    // aitree_variable at offset 0x258
    int* mLynelAIFlags_a{};
    // aitree_variable at offset 0x260
    int* mLynelAreaAlarmPoint_a{};
    // aitree_variable at offset 0x268
    void* mLynelBodyControlUnit_a{};
    // aitree_variable at offset 0x270
    void* mLynelMoveParam_a{};
};

}  // namespace uking::ai
