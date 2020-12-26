#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class On : public ActionEx {
    SEAD_RTTI_OVERRIDE(On, ActionEx)
public:
    explicit On(const InitArg& arg);
    ~On() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mLinkTagType_s{};
    // static_param at offset 0x28
    const int* mTargetIdx_s{};
    // static_param at offset 0x30
    const int* mSeqBankIdx_s{};
    // static_param at offset 0x38
    const bool* mOnWaitRevival_s{};
    // static_param at offset 0x40
    const bool* mIsIgnoreSame_s{};
    // static_param at offset 0x48
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
