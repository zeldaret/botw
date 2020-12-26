#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LastBossThunderAppear : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LastBossThunderAppear, ksys::act::ai::Action)
public:
    explicit LastBossThunderAppear(const InitArg& arg);
    ~LastBossThunderAppear() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAtMinDamage_s{};
    // static_param at offset 0x28
    const float* mAppearTime_s{};
    // map_unit_param at offset 0x30
    const int* mAtMinDamage_m{};
    // map_unit_param at offset 0x38
    const int* mAttackPower_m{};
    // map_unit_param at offset 0x40
    const int* mAttackPowerForPlayer_m{};
};

}  // namespace uking::action
