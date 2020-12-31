#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosDynParamRot : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPosDynParamRot, TargetPosAI)
public:
    explicit TargetPosDynParamRot(const InitArg& arg);
    ~TargetPosDynParamRot() override;

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
