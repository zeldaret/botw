#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TurnPreAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TurnPreAction, ksys::act::ai::Ai)
public:
    explicit TurnPreAction(const InitArg& arg);
    ~TurnPreAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
