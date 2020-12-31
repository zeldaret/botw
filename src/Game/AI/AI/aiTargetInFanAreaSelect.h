#pragma once

#include "Game/AI/AI/aiTargetInAreaSelect.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetInFanAreaSelect : public TargetInAreaSelect {
    SEAD_RTTI_OVERRIDE(TargetInFanAreaSelect, TargetInAreaSelect)
public:
    explicit TargetInFanAreaSelect(const InitArg& arg);
    ~TargetInFanAreaSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mNearYMax_s{};
    // static_param at offset 0x48
    const float* mNearYMin_s{};
    // static_param at offset 0x50
    const float* mFarYMax_s{};
    // static_param at offset 0x58
    const float* mFarYMin_s{};
    // static_param at offset 0x60
    const float* mXZRange_s{};
    // static_param at offset 0x68
    const float* mAngle_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
