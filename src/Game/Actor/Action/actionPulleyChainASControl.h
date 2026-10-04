#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PulleyChainASControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PulleyChainASControl, ksys::act::ai::Action)
public:
    explicit PulleyChainASControl(const InitArg& arg);
    ~PulleyChainASControl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTargetIdx_s{};
    // static_param at offset 0x28
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
