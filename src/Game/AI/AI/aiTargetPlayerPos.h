#pragma once

#include "Game/AI/AI/aiTargetPosAI.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPlayerPos : public TargetPosAI {
    SEAD_RTTI_OVERRIDE(TargetPlayerPos, TargetPosAI)
public:
    explicit TargetPlayerPos(const InitArg& arg);
    ~TargetPlayerPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
