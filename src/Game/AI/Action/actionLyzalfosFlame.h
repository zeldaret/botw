#pragma once

#include "Game/AI/Action/actionChemicalAttackBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LyzalfosFlame : public ChemicalAttackBall {
    SEAD_RTTI_OVERRIDE(LyzalfosFlame, ChemicalAttackBall)
public:
    explicit LyzalfosFlame(const InitArg& arg);
    ~LyzalfosFlame() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x90
    const int* mLengthFrame_s{};
    // static_param at offset 0x98
    const int* mAtResetTime_s{};
    // static_param at offset 0xa0
    const int* mAtChaseFrame_s{};
    // static_param at offset 0xa8
    const int* mBindGrabNodeIdx_s{};
    // static_param at offset 0xb0
    const float* mChaseMax_s{};
    // static_param at offset 0xb8
    const float* mChaseRate_s{};
    // static_param at offset 0xc0
    const sead::Vector3f* mOffsetRot_s{};
};

}  // namespace uking::action
