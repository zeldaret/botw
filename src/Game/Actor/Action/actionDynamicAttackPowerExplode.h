#pragma once

#include "Game/Actor/Action/actionEitherSideExplode.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DynamicAttackPowerExplode : public EitherSideExplode {
    SEAD_RTTI_OVERRIDE(DynamicAttackPowerExplode, EitherSideExplode)
public:
    explicit DynamicAttackPowerExplode(const InitArg& arg);
    ~DynamicAttackPowerExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x88
    const int* mAttackPower_s{};
    // static_param at offset 0x90
    const int* mMinDamage_s{};
    // static_param at offset 0x98
    const int* mPlayerDamage_s{};
};

}  // namespace uking::action
