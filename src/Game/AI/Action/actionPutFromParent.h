#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PutFromParent : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PutFromParent, ksys::act::ai::Action)
public:
    explicit PutFromParent(const InitArg& arg);
    ~PutFromParent() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mTimer_s{};
    // static_param at offset 0x28
    sead::SafeString mHoldOffXLinkKey_s{};
};

}  // namespace uking::action
