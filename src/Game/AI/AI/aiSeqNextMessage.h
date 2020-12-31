#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqNextMessage : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqNextMessage, SeqTwoAction)
public:
    explicit SeqNextMessage(const InitArg& arg);
    ~SeqNextMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mDelayTimeMax_s{};
};

}  // namespace uking::ai
