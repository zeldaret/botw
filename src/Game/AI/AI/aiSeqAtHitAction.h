#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqAtHitAction : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqAtHitAction, SeqTwoAction)
public:
    explicit SeqAtHitAction(const InitArg& arg);
    ~SeqAtHitAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
