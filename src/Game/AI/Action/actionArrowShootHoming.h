#pragma once

#include "Game/AI/Action/actionArrowShootMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowShootHoming : public ArrowShootMove {
    SEAD_RTTI_OVERRIDE(ArrowShootHoming, ArrowShootMove)
public:
    explicit ArrowShootHoming(const InitArg& arg);
    ~ArrowShootHoming() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x150
    const float* mSubAngMax_s{};
    // static_param at offset 0x158
    const float* mHomingRate_s{};
    // static_param at offset 0x160
    const float* mNearDist_s{};
    // dynamic_param at offset 0x168
    ksys::act::BaseProcLink* mTargetActor_d{};
    // dynamic_param at offset 0x170
    sead::Vector3f* mHomingTargetPos_d{};
};

}  // namespace uking::action
