#pragma once

#include "Game/AI/Action/actionWaterUpDownAnmDrivenMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterUpDownDrivenPreAttack : public WaterUpDownAnmDrivenMove {
    SEAD_RTTI_OVERRIDE(WaterUpDownDrivenPreAttack, WaterUpDownAnmDrivenMove)
public:
    explicit WaterUpDownDrivenPreAttack(const InitArg& arg);
    ~WaterUpDownDrivenPreAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x68
    const float* mTurnSpeed_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
