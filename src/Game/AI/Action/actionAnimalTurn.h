#pragma once

#include "Game/AI/Action/actionPlayASForAnimalUnit.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalTurn : public PlayASForAnimalUnit {
    SEAD_RTTI_OVERRIDE(AnimalTurn, PlayASForAnimalUnit)
public:
    explicit AnimalTurn(const InitArg& arg);
    ~AnimalTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x60
    const float* mAnimPlayRate_s{};
    // static_param at offset 0x68
    const float* mFinishAngleRange_s{};
    // static_param at offset 0x70
    const float* mRotateAngleMax_s{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
