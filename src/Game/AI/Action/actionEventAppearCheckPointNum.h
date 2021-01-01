#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventAppearCheckPointNum : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventAppearCheckPointNum, ksys::act::ai::Action)
public:
    explicit EventAppearCheckPointNum(const InitArg& arg);
    ~EventAppearCheckPointNum() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mIconType_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mGameDataIntTargetCounter_d{};
};

}  // namespace uking::action
