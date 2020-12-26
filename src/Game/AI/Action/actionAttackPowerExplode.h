#pragma once

#include "Game/AI/Action/actionExplode.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AttackPowerExplode : public Explode {
    SEAD_RTTI_OVERRIDE(AttackPowerExplode, Explode)
public:
    explicit AttackPowerExplode(const InitArg& arg);
    ~AttackPowerExplode() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x80
    bool* mIsPlayerAttack_d{};
};

}  // namespace uking::action
