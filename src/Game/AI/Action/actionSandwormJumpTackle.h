#pragma once

#include "Game/AI/Action/actionJumpTackle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormJumpTackle : public JumpTackle {
    SEAD_RTTI_OVERRIDE(SandwormJumpTackle, JumpTackle)
public:
    explicit SandwormJumpTackle(const InitArg& arg);
    ~SandwormJumpTackle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mPosReduceRate_s{};
    // static_param at offset 0xa0
    const float* mGravityScale_s{};
    // static_param at offset 0xa8
    sead::SafeString mAtkColName_s{};
    // dynamic_param at offset 0xb8
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::action
