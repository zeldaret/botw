#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LumberjackFallenTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LumberjackFallenTree, ksys::act::ai::Ai)
public:
    explicit LumberjackFallenTree(const InitArg& arg);
    ~LumberjackFallenTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x60];
    // static_param at offset 0x98
    const float* mToLogAngVel_s{};
    // static_param at offset 0xa0
    const float* mMaxCheckAng_s{};
    // static_param at offset 0xa8
    const float* mCheckDis_s{};
    // static_param at offset 0xb0
    const float* mCheckHeightRate_s{};
    // static_param at offset 0xb8
    const float* mTerrorRegistAng_s{};
    // static_param at offset 0xc0
    const float* mTerrorUnregistTimelimit_s{};
    // static_param at offset 0xc8
    const float* mNoiseLevel_s{};
    // static_param at offset 0xd0
    const bool* mIsCheckHeight_s{};
    // static_param at offset 0xd8
    const sead::Vector3f* mTerrorOffsetPos4Falling_s{};
    // aitree_variable at offset 0xe0
    int* mLumberjackType_a{};
    // aitree_variable at offset 0xe8
    sead::Vector3f* mForceSetDropPos_a{};
    // aitree_variable at offset 0xf0
    sead::Vector3f* mMoveDirection_a{};
};

}  // namespace uking::ai
