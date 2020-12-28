#pragma once

#include "Game/AI/Action/actionFreezedInIce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FreezedInIceWeapon : public FreezedInIce {
    SEAD_RTTI_OVERRIDE(FreezedInIceWeapon, FreezedInIce)
public:
    explicit FreezedInIceWeapon(const InitArg& arg);
    ~FreezedInIceWeapon() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
