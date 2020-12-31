#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTwoWeakPointOnFirstDo : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqTwoWeakPointOnFirstDo, SeqTwoAction)
public:
    explicit SeqTwoWeakPointOnFirstDo(const InitArg& arg);
    ~SeqTwoWeakPointOnFirstDo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x50
    bool* mIsWeakPointAppearMode_a{};
};

}  // namespace uking::ai
