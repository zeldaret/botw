#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalEnemyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StalEnemyRoot, ksys::act::ai::Ai)
public:
    explicit StalEnemyRoot(const InitArg& arg);
    ~StalEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x30];
    // static_param at offset 0x68
    const int* mDeadCount_s{};
    // static_param at offset 0x70
    const float* mSearchFrame_s{};
    // static_param at offset 0x78
    const float* mInWaterDepth_s{};
    // static_param at offset 0x80
    const float* mOutOfWaterOffset_s{};
    // static_param at offset 0x88
    const float* mDeadCheckFrame_s{};
    // static_param at offset 0x90
    const float* mSpreadDist_s{};
    // static_param at offset 0x98
    const float* mSmallSpreadDist_s{};
    // static_param at offset 0xa0
    const float* mSearchDistXZ_s{};
    // static_param at offset 0xa8
    const float* mSearchDistY_s{};
    // static_param at offset 0xb0
    const float* mFallHeight_s{};
    // map_unit_param at offset 0xb8
    const bool* mIsCreateStalPart_m{};
    // aitree_variable at offset 0xc0
    bool* mIsStopFallCheck_a{};
    // aitree_variable at offset 0xc8
    void* mStalEnemyUnit_a{};
};

}  // namespace uking::ai
