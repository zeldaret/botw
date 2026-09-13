#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EndChangeableASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EndChangeableASPlay, ksys::act::ai::Action)
public:
    explicit EndChangeableASPlay(const InitArg& arg);
    ~EndChangeableASPlay() override;

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
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
