#pragma once

#include "Game/AI/Action/actionChargeAndShoot.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnAndChargeAndShoot : public ChargeAndShoot {
    SEAD_RTTI_OVERRIDE(TurnAndChargeAndShoot, ChargeAndShoot)
public:
    explicit TurnAndChargeAndShoot(const InitArg& arg);
    ~TurnAndChargeAndShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const float* mRotSpeed_s{};
};

}  // namespace uking::action
