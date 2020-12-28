#pragma once

#include "Game/AI/Action/actionDieAnm.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DieAnmDropWeapon : public DieAnm {
    SEAD_RTTI_OVERRIDE(DieAnmDropWeapon, DieAnm)
public:
    explicit DieAnmDropWeapon(const InitArg& arg);
    ~DieAnmDropWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    const float* mWeaponDropSpeedY_s{};
};

}  // namespace uking::action
