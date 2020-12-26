#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetTargetFrameMtx : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetTargetFrameMtx, ksys::act::ai::Action)
public:
    explicit SetTargetFrameMtx(const InitArg& arg);
    ~SetTargetFrameMtx() override;

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
    const float* mTargetFrame_s{};
    // static_param at offset 0x38
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x40
    const bool* mResetTransBoneOnLeave_s{};
    // static_param at offset 0x48
    const bool* mIsHomeMtx_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
