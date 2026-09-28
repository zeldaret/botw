#pragma once

#include "Game/Actor/Action/actionAttackWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantDownSwingAttack : public AttackWithAS {
    SEAD_RTTI_OVERRIDE(GiantDownSwingAttack, AttackWithAS)
public:
    explicit GiantDownSwingAttack(const InitArg& arg);
    ~GiantDownSwingAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const int* mWeaponIdx_s{};
};

}  // namespace uking::action
