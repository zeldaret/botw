#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeScheduleAnchor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeScheduleAnchor, ksys::act::ai::Action)
public:
    explicit ChangeScheduleAnchor(const InitArg& arg);
    ~ChangeScheduleAnchor() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    sead::SafeString mScheduleName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mAnchorUniqueName_d{};
};

}  // namespace uking::action
