#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetKnockBackBasePos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetKnockBackBasePos, TargetPosAI)
public:
    explicit TargetKnockBackBasePos(const InitArg& arg);
    ~TargetKnockBackBasePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
