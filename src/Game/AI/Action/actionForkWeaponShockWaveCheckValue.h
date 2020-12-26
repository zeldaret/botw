#pragma once

#include "Game/AI/Action/actionForkWeaponShockWave.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponShockWaveCheckValue : public ForkWeaponShockWave {
    SEAD_RTTI_OVERRIDE(ForkWeaponShockWaveCheckValue, ForkWeaponShockWave)
public:
    explicit ForkWeaponShockWaveCheckValue(const InitArg& arg);
    ~ForkWeaponShockWaveCheckValue() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    sead::SafeString mAtEventValue_s{};
};

}  // namespace uking::action
