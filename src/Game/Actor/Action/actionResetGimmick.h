#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ResetGimmick : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ResetGimmick, ksys::act::ai::Action)
public:
    explicit ResetGimmick(const InitArg& arg);
    ~ResetGimmick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mSystemResetOption_d{};
    // dynamic_param at offset 0x28
    bool* mIsResetCamera_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mAdditionalResetActor_d{};
};

}  // namespace uking::action
