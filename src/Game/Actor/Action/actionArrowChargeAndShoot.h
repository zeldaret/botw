#pragma once

#include "Game/Actor/Action/actionShootArrow.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ArrowChargeAndShoot : public ShootArrow {
    SEAD_RTTI_OVERRIDE(ArrowChargeAndShoot, ShootArrow)
public:
    explicit ArrowChargeAndShoot(const InitArg& arg);
    ~ArrowChargeAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
