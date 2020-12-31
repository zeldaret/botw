#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantChanceWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ForestGiantChanceWait, ksys::act::ai::Ai)
public:
    explicit ForestGiantChanceWait(const InitArg& arg);
    ~ForestGiantChanceWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mChanceRate_s{};
    // static_param at offset 0x40
    const int* mCorrectRate_s{};
    // static_param at offset 0x48
    const float* mTurnStartAngle_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
