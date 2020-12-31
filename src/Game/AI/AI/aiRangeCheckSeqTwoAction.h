#pragma once

#include "Game/AI/AI/aiSeqTargetTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeCheckSeqTwoAction : public SeqTargetTwoAction {
    SEAD_RTTI_OVERRIDE(RangeCheckSeqTwoAction, SeqTargetTwoAction)
public:
    explicit RangeCheckSeqTwoAction(const InitArg& arg);
    ~RangeCheckSeqTwoAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x48
    const float* mRange_s{};
    // static_param at offset 0x50
    const bool* mCheckFar_s{};
};

}  // namespace uking::ai
