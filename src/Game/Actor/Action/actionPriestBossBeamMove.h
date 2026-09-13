#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PriestBossBeamMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PriestBossBeamMove, ksys::act::ai::Action)
public:
    explicit PriestBossBeamMove(const InitArg& arg);
    ~PriestBossBeamMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const int* mShieldDamage_s{};
    // static_param at offset 0x30
    const int* mContactWaitFrame_s{};
    // static_param at offset 0x38
    const float* mReflectDeccel_s{};
    // map_unit_param at offset 0x40
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x48
    const int* mAttackPowerForPlayer_m{};
    // map_unit_param at offset 0x50
    const sead::Vector3f* mPosOffset_m{};
};

}  // namespace uking::action
