#pragma once

#include "Game/Actor/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetLastDamagedPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetLastDamagedPos, TargetPosAI)
public:
    explicit TargetLastDamagedPos(const InitArg& arg);
    ~TargetLastDamagedPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
