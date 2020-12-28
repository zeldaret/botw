#pragma once

#include "Game/AI/Action/actionShock.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShockDynamicWeapon : public Shock {
    SEAD_RTTI_OVERRIDE(ShockDynamicWeapon, Shock)
public:
    explicit ShockDynamicWeapon(const InitArg& arg);
    ~ShockDynamicWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    ksys::act::BaseProcLink* mDropWeapon_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mDropDir_d{};
};

}  // namespace uking::action
