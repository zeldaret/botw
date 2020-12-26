#pragma once

#include "Game/AI/Action/actionForkWeaponAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponAttackWithAtkBody : public ForkWeaponAttack {
    SEAD_RTTI_OVERRIDE(ForkWeaponAttackWithAtkBody, ForkWeaponAttack)
public:
    explicit ForkWeaponAttackWithAtkBody(const InitArg& arg);
    ~ForkWeaponAttackWithAtkBody() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    sead::SafeString mAtkBodyName_s{};
};

}  // namespace uking::action
