#pragma once

#include "Game/AI/Action/actionForkDropWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkInWaterDropWeaponWithSpeed : public ForkDropWeapon {
    SEAD_RTTI_OVERRIDE(ForkInWaterDropWeaponWithSpeed, ForkDropWeapon)
public:
    explicit ForkInWaterDropWeaponWithSpeed(const InitArg& arg);
    ~ForkInWaterDropWeaponWithSpeed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mInWaterDepth_s{};
    // static_param at offset 0x50
    const float* mOutWaterDepth_s{};
};

}  // namespace uking::action
