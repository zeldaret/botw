#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetHomePos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetHomePos, TargetActorPos)
public:
    explicit TargetHomePos(const InitArg& arg);
    ~TargetHomePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
