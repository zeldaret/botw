#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosAnchorOffsetTarget : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPosAnchorOffsetTarget, TargetPosAI)
public:
    explicit TargetPosAnchorOffsetTarget(const InitArg& arg);
    ~TargetPosAnchorOffsetTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mDist_s{};
    // static_param at offset 0x48
    sead::SafeString mAnchorName_s{};
};

}  // namespace uking::ai
