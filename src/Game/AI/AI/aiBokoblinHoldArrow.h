#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinHoldArrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinHoldArrow, ksys::act::ai::Ai)
public:
    explicit BokoblinHoldArrow(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
