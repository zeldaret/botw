#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PrevASSkipSeq : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(PrevASSkipSeq, SeqTwoAction)
public:
    explicit PrevASSkipSeq(const InitArg& arg);
    ~PrevASSkipSeq() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    sead::SafeString mPrevASName_s{};
};

}  // namespace uking::ai
