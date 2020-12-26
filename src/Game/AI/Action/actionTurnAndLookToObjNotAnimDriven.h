#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnAndLookToObjNotAnimDriven : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(TurnAndLookToObjNotAnimDriven, LookAtObjectBase)
public:
    explicit TurnAndLookToObjNotAnimDriven(const InitArg& arg);
    ~TurnAndLookToObjNotAnimDriven() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc8
    float* mRotSpdMax_d{};
    // dynamic_param at offset 0xd0
    float* mRotSpdMin_d{};
    // dynamic_param at offset 0xd8
    float* mRotInitSpd_d{};
    // dynamic_param at offset 0xe0
    float* mRotAccel_d{};
    // dynamic_param at offset 0xe8
    float* mRotRate_d{};
};

}  // namespace uking::action
