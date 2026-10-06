#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetLastAttackerPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetLastAttackerPos, TargetActorPos)
public:
    explicit TargetLastAttackerPos(const InitArg& arg);
    ~TargetLastAttackerPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
