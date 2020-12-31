#pragma once

#include "Game/AI/AI/aiCircleMove.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CircleMoveTarget : public CircleMove {
    SEAD_RTTI_OVERRIDE(CircleMoveTarget, CircleMove)
public:
    explicit CircleMoveTarget(const InitArg& arg);
    ~CircleMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
