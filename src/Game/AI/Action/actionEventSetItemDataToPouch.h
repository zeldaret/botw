#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSetItemDataToPouch : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSetItemDataToPouch, ksys::act::ai::Action)
public:
    explicit EventSetItemDataToPouch(const InitArg& arg);
    ~EventSetItemDataToPouch() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mSharpWeaponAddValue_d{};
    // dynamic_param at offset 0x28
    int* mSharpWeaponAddType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mTargetActorName_d{};
};

}  // namespace uking::action
