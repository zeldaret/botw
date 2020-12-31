#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetDynamicActorPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetDynamicActorPos, TargetPosAI)
public:
    explicit TargetDynamicActorPos(const InitArg& arg);
    ~TargetDynamicActorPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x40
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
