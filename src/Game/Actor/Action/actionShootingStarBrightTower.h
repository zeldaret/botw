#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShootingStarBrightTower : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShootingStarBrightTower, ksys::act::ai::Action)
public:
    explicit ShootingStarBrightTower(const InitArg& arg);
    ~ShootingStarBrightTower() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDisappearDistance_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mHitGroundAngle_d{};
};

}  // namespace uking::action
