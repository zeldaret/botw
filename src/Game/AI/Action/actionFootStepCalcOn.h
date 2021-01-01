#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FootStepCalcOn : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FootStepCalcOn, ksys::act::ai::Action)
public:
    explicit FootStepCalcOn(const InitArg& arg);
    ~FootStepCalcOn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mActor_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mInstanceName_d{};
};

}  // namespace uking::action
