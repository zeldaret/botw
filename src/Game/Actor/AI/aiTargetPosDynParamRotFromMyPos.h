#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosDynParamRotFromMyPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetPosDynParamRotFromMyPos, TargetActorPos)
public:
    explicit TargetPosDynParamRotFromMyPos(const InitArg& arg);
    ~TargetPosDynParamRotFromMyPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mMinDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mAngle_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
