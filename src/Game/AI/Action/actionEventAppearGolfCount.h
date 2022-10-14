#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAppearGolfCount : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAppearGolfCount, ksys::act::ai::Action)
public:
    explicit EventAppearGolfCount(const InitArg& arg);
    ~EventAppearGolfCount() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mGameDataIntTargetCounter_d{};
};

}  // namespace uking::action
