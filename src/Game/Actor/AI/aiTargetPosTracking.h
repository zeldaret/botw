#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosTracking : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetPosTracking, ksys::act::ai::Ai)
public:
    explicit TargetPosTracking(const InitArg& arg);
    ~TargetPosTracking() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTrackSpeed_s{};
    // static_param at offset 0x40
    const bool* mIsStoppedByJustAvoid_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
