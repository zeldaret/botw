#pragma once

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowSkyShootMove : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowSkyShootMove, ArrowShootMove)
public:
    explicit ArrowSkyShootMove(const InitArg& arg);
    ~ArrowSkyShootMove() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x150
    const int* mInterval_s{};
    // static_param at offset 0x158
    const float* mSkyShootDist_s{};
    // dynamic_param at offset 0x160
    ksys::act::BaseProcLink* mTargetActor_d{};
    // dynamic_param at offset 0x168
    sead::Vector3f* mPosOffset_d{};
};

}  // namespace uking::action
