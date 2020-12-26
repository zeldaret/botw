#pragma once

#include "Game/AI/Action/actionForkNoWeaponAttackBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkNoWeaponAttackAllTime : public ForkNoWeaponAttackBase {
    SEAD_RTTI_OVERRIDE(ForkNoWeaponAttackAllTime, ForkNoWeaponAttackBase)
public:
    explicit ForkNoWeaponAttackAllTime(const InitArg& arg);
    ~ForkNoWeaponAttackAllTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    sead::SafeString mAtDirString_s{};
};

}  // namespace uking::action
