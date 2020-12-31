#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavViewMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NavViewMove, ksys::act::ai::Ai)
public:
    explicit NavViewMove(const InitArg& arg);
    ~NavViewMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSubsAngle_s{};
    // static_param at offset 0x40
    const bool* mCheckOnce_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
