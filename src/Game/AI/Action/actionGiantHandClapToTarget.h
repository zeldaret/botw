#pragma once

#include "Game/AI/Action/actionPunchAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantHandClapToTarget : public PunchAttack {
    SEAD_RTTI_OVERRIDE(GiantHandClapToTarget, PunchAttack)
public:
    explicit GiantHandClapToTarget(const InitArg& arg);
    ~GiantHandClapToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const float* mAtkBodyScale_s{};
    // dynamic_param at offset 0xd8
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
