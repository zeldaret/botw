#pragma once

#include "Game/AI/Action/actionForkDropWeaponWithSpeed.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerForkDropWeaponWithSpeed : public ForkDropWeaponWithSpeed {
    SEAD_RTTI_OVERRIDE(PlayerForkDropWeaponWithSpeed, ForkDropWeaponWithSpeed)
public:
    explicit PlayerForkDropWeaponWithSpeed(const InitArg& arg);
    ~PlayerForkDropWeaponWithSpeed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
