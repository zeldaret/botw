#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosRotFromMyPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPosRotFromMyPos, TargetPosAI)
public:
    explicit TargetPosRotFromMyPos(const InitArg& arg);
    ~TargetPosRotFromMyPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mMinDist_s{};
    // static_param at offset 0x48
    const bool* mIsRandSign_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mAngle_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
