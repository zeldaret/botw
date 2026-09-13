#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkClothOnOffASPlay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkClothOnOffASPlay, ksys::act::ai::Action)
public:
    explicit ForkClothOnOffASPlay(const InitArg& arg);
    ~ForkClothOnOffASPlay() override;

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
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
    // static_param at offset 0x58
    sead::SafeString mClothOffASName_s{};
};

}  // namespace uking::action
