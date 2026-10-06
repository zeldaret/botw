#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetLastAttackedPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetLastAttackedPos, TargetActorPos)
public:
    explicit TargetLastAttackedPos(const InitArg& arg);
    ~TargetLastAttackedPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
