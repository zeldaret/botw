#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(GuardianMiniRoot, EnemyRoot)
public:
    explicit GuardianMiniRoot(const InitArg& arg);
    ~GuardianMiniRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const float* mNeckRotRatio_s{};
    // static_param at offset 0x1e0
    const int* mJustGuardNumForBreak_s{};
    // static_param at offset 0x1e8
    const float* mRotStopSpeed_s{};
    // aitree_variable at offset 0x1f0
    int* mDamagedCount_a{};
    // aitree_variable at offset 0x1f8
    bool* mIsTransformedGuardianMini_a{};
    // aitree_variable at offset 0x200
    int* mGuardianMiniChanceTimeState_a{};
};

}  // namespace uking::ai
