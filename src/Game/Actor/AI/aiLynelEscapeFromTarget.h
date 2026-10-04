#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelEscapeFromTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelEscapeFromTarget, ksys::act::ai::Ai)
public:
    explicit LynelEscapeFromTarget(const InitArg& arg);
    ~LynelEscapeFromTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mKeepTime_s{};
    // static_param at offset 0x40
    const float* mSpaceDistMin_s{};
    // static_param at offset 0x48
    const float* mSpaceDist_s{};
    // static_param at offset 0x50
    const float* mMoveDistMin_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
