#pragma once

#include "Game/AI/Action/actionMoveWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormMove : public MoveWithAS {
    SEAD_RTTI_OVERRIDE(SandwormMove, MoveWithAS)
public:
    explicit SandwormMove(const InitArg& arg);
    ~SandwormMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xf0
    const float* mTargetSandOffset_s{};
    // static_param at offset 0xf8
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0x100
    const float* mVibrateStopCheck_s{};
    // static_param at offset 0x108
    const float* mVibrateCheckFrame_s{};
    // static_param at offset 0x110
    const float* mVibrateMemoryStep_s{};
    // static_param at offset 0x118
    const bool* mIsCheckAnmSeqCancel_s{};
    // aitree_variable at offset 0x120
    void* mRefPosVibrateChecker_a{};
};

}  // namespace uking::action
