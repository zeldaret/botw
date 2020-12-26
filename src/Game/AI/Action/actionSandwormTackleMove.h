#pragma once

#include "Game/AI/Action/actionAtkTackleMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormTackleMove : public AtkTackleMove {
    SEAD_RTTI_OVERRIDE(SandwormTackleMove, AtkTackleMove)
public:
    explicit SandwormTackleMove(const InitArg& arg);
    ~SandwormTackleMove() override;

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
    const float* mEatRadius_s{};
    // static_param at offset 0xd8
    sead::SafeString mEatNode_s{};
    // static_param at offset 0xe8
    const sead::Vector3f* mEatOffset_s{};
};

}  // namespace uking::action
