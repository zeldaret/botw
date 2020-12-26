#pragma once

#include "Game/AI/Action/actionForkLynelDrawWeaponASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelDrawWeapon : public ForkLynelDrawWeaponASPlay {
    SEAD_RTTI_OVERRIDE(LynelDrawWeapon, ForkLynelDrawWeaponASPlay)
public:
    explicit LynelDrawWeapon(const InitArg& arg);
    ~LynelDrawWeapon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
