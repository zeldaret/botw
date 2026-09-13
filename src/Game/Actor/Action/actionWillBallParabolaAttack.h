#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WillBallParabolaAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WillBallParabolaAttack, ksys::act::ai::Action)
public:
    explicit WillBallParabolaAttack(const InitArg& arg);
    ~WillBallParabolaAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mMaxSpeed_s{};
    // static_param at offset 0x28
    const float* mMaxHeight_s{};
    // static_param at offset 0x30
    const float* mMinMoveXZ_s{};
    // static_param at offset 0x38
    const float* mGravityScale_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
