#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetTargetPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetTargetPos, TargetActorPos)
public:
    explicit TargetTargetPos(const InitArg& arg);
    ~TargetTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mAddSpeed_s{};
};

}  // namespace uking::ai
