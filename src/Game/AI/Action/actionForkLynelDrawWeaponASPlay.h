#pragma once

#include "Game/AI/Action/actionForkLynelDrawWeapon.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkLynelDrawWeaponASPlay : public ForkLynelDrawWeapon {
    SEAD_RTTI_OVERRIDE(ForkLynelDrawWeaponASPlay, ForkLynelDrawWeapon)
public:
    explicit ForkLynelDrawWeaponASPlay(const InitArg& arg);
    ~ForkLynelDrawWeaponASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
