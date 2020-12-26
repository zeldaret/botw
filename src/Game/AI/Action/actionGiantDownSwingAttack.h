#pragma once

#include "Game/AI/Action/actionGiantAttackWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantDownSwingAttack : public GiantAttackWithAS {
    SEAD_RTTI_OVERRIDE(GiantDownSwingAttack, GiantAttackWithAS)
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
