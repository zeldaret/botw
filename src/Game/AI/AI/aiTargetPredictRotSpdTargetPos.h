#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPredictRotSpdTargetPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPredictRotSpdTargetPos, TargetPosAI)
public:
    explicit TargetPredictRotSpdTargetPos(const InitArg& arg);
    ~TargetPredictRotSpdTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mAddSpeed_s{};
};

}  // namespace uking::ai
