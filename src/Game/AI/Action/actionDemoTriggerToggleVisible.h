#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoTriggerToggleVisible : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoTriggerToggleVisible, ksys::act::ai::Action)
public:
    explicit DemoTriggerToggleVisible(const InitArg& arg);
    ~DemoTriggerToggleVisible() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    bool* mIsVisible_d{};
    // dynamic_param at offset 0x28
    bool* mIsXLinkHandling_d{};
    // dynamic_param at offset 0x30
    bool* mIsClothHandling_d{};
};

}  // namespace uking::action
