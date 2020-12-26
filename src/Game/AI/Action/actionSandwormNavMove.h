#pragma once

#include "Game/AI/Action/actionNavMeshMoveWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormNavMove : public NavMeshMoveWithAS {
    SEAD_RTTI_OVERRIDE(SandwormNavMove, NavMeshMoveWithAS)
public:
    explicit SandwormNavMove(const InitArg& arg);
    ~SandwormNavMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const float* mTargetSandOffset_s{};
    // static_param at offset 0xc8
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0xd0
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0xd8
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0xe0
    const float* mVibrateMemoryStep_s{};
    // aitree_variable at offset 0xe8
    void* mRefPosVibrateChecker_a{};
};

}  // namespace uking::action
