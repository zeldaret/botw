#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventCheckAndCreateEquip : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventCheckAndCreateEquip, ksys::act::ai::Action)
public:
    explicit EventCheckAndCreateEquip(const InitArg& arg);
    ~EventCheckAndCreateEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mSharpWeaponAddValue_d{};
    // dynamic_param at offset 0x28
    int* mSharpWeaponAddType_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mTargetActorName_d{};
};

}  // namespace uking::action
