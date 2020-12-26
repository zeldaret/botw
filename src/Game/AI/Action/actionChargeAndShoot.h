#pragma once

#include "Game/AI/Action/actionShootArrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChargeAndShoot : public ShootArrow {
    SEAD_RTTI_OVERRIDE(ChargeAndShoot, ShootArrow)
public:
    explicit ChargeAndShoot(const InitArg& arg);
    ~ChargeAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
