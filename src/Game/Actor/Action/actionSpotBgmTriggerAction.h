#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SpotBgmTriggerAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SpotBgmTriggerAction, ksys::act::ai::Action)
public:
    explicit SpotBgmTriggerAction(const InitArg& arg);
    ~SpotBgmTriggerAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mSound_d{};
    // map_unit_param at offset 0x30
    const bool* mIsStopWithoutReductionY_m{};
    // map_unit_param at offset 0x38
    sead::SafeString mSound_m{};
};

}  // namespace uking::action
