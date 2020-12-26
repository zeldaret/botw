#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseElectricParalysis : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(HorseElectricParalysis, ActionWithPosAngReduce)
public:
    explicit HorseElectricParalysis(const InitArg& arg);
    ~HorseElectricParalysis() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const float* mPauseDelayFrames_s{};
    // static_param at offset 0x38
    const bool* mCanRiddenWhenLeave_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // static_param at offset 0x50
    sead::SafeString mThrowOffAttackRigidBodyName_s{};
    // dynamic_param at offset 0x60
    bool* mIsEnableThrowOffAttack_d{};
};

}  // namespace uking::action
