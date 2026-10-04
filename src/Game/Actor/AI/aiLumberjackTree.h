#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LumberjackTree : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LumberjackTree, ksys::act::ai::Ai)
public:
    explicit LumberjackTree(const InitArg& arg);
    ~LumberjackTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x218];
    // static_param at offset 0x250
    const float* mFallInterval_s{};
    // static_param at offset 0x258
    const float* mFellImpRate_s{};
    // static_param at offset 0x260
    const float* mFellRotRate_s{};
    // static_param at offset 0x268
    const float* mCutOffsetLower_s{};
    // static_param at offset 0x270
    const float* mCutOffsetUpper_s{};
    // static_param at offset 0x278
    const float* mAlphaLower_s{};
    // static_param at offset 0x280
    const float* mAlphaSpeed_s{};
    // map_unit_param at offset 0x288
    const float* mCutRate_m{};
    // map_unit_param at offset 0x290
    const float* mAngleY_m{};
    // map_unit_param at offset 0x298
    sead::SafeString mDropTable_m{};
    // aitree_variable at offset 0x2a8
    int* mLumberjackType_a{};
    // aitree_variable at offset 0x2b0
    sead::Vector3f* mForceSetDropPos_a{};
    // aitree_variable at offset 0x2b8
    sead::Vector3f* mMoveDirection_a{};
};

}  // namespace uking::ai
