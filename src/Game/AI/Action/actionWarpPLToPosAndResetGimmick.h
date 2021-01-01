#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpPLToPosAndResetGimmick : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpPLToPosAndResetGimmick, ksys::act::ai::Action)
public:
    explicit WarpPLToPosAndResetGimmick(const InitArg& arg);
    ~WarpPLToPosAndResetGimmick() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mRotationY_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mDestination_d{};
    // dynamic_param at offset 0x30
    int* mSystemResetOption_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mAdditionalResetActor_d{};
};

}  // namespace uking::action
