#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPLAndResetGimmick : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPLAndResetGimmick, ksys::act::ai::Action)
public:
    explicit WarpPLAndResetGimmick(const InitArg& arg);
    ~WarpPLAndResetGimmick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mSystemResetOption_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mStartPosName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mAdditionalResetActor_d{};
};

}  // namespace uking::action
