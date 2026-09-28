#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPredictRotSpdTargetPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetPredictRotSpdTargetPos, TargetActorPos)
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
