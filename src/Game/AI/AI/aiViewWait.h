#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ViewWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ViewWait, ksys::act::ai::Ai)
public:
    explicit ViewWait(const InitArg& arg);
    ~ViewWait() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnStartAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
