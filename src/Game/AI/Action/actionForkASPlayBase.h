#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASPlayBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASPlayBase, ksys::act::ai::Action)
public:
    explicit ForkASPlayBase(const InitArg& arg);
    ~ForkASPlayBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mEndState_s{};
    // static_param at offset 0x28
    const int* mChangeableTiming_s{};
    // static_param at offset 0x30
    const int* mSeqBank_s{};
    // static_param at offset 0x38
    const int* mTargetBone_s{};
    // static_param at offset 0x40
    const float* mFirstRandomRatio_s{};
    // static_param at offset 0x48
    const bool* mIsIgnoreSame_s{};
};

}  // namespace uking::action
