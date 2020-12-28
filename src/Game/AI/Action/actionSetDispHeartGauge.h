#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetDispHeartGauge : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetDispHeartGauge, ksys::act::ai::Action)
public:
    explicit SetDispHeartGauge(const InitArg& arg);
    ~SetDispHeartGauge() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsDisplay_d{};
    // dynamic_param at offset 0x28
    bool* mIsDisplayEx_d{};
    // dynamic_param at offset 0x30
    bool* mIsGetDemo_d{};
};

}  // namespace uking::action
