#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TreasureBoxOpenWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(TreasureBoxOpenWait, ksys::act::ai::Action)
public:
    explicit TreasureBoxOpenWait(const InitArg& arg);
    ~TreasureBoxOpenWait() override;

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
    // static_param at offset 0x48
    sead::SafeString mASName_PreOpen_s{};
    // aitree_variable at offset 0x58
    bool* mIsOpenTreasureBox_a{};
};

}  // namespace uking::action
