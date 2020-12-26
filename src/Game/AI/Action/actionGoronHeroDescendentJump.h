#pragma once

#include "Game/AI/Action/actionMoveToTargetCurveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GoronHeroDescendentJump : public MoveToTargetCurveBase {
    SEAD_RTTI_OVERRIDE(GoronHeroDescendentJump, MoveToTargetCurveBase)
public:
    explicit GoronHeroDescendentJump(const InitArg& arg);
    ~GoronHeroDescendentJump() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x68
    bool* mIsIntoCannon_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mJumpTargetPos_d{};
};

}  // namespace uking::action
