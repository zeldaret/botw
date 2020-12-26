#pragma once

#include "Game/AI/Action/actionLinearFlyAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SpinFlyAttack : public LinearFlyAttack {
    SEAD_RTTI_OVERRIDE(SpinFlyAttack, LinearFlyAttack)
public:
    explicit SpinFlyAttack(const InitArg& arg);
    ~SpinFlyAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd8
    const float* mRotSpeed_s{};
};

}  // namespace uking::action
