#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkToggleWeaponXLinkSleep : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkToggleWeaponXLinkSleep, ksys::act::ai::Action)
public:
    explicit ForkToggleWeaponXLinkSleep(const InitArg& arg);
    ~ForkToggleWeaponXLinkSleep() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x20
    const int* mToggle_s{};
};

}  // namespace uking::action
