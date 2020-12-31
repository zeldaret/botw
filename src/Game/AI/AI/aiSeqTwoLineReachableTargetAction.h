#pragma once

#include "Game/AI/AI/aiSeqTwoLineReachableTargetActionBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTwoLineReachableTargetAction : public SeqTwoLineReachableTargetActionBase {
    SEAD_RTTI_OVERRIDE(SeqTwoLineReachableTargetAction, SeqTwoLineReachableTargetActionBase)
public:
    explicit SeqTwoLineReachableTargetAction(const InitArg& arg);
    ~SeqTwoLineReachableTargetAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
