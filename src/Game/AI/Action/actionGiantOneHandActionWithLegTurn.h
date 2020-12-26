#pragma once

#include "Game/AI/Action/actionGiantAttackWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandActionWithLegTurn : public GiantAttackWithAS {
    SEAD_RTTI_OVERRIDE(GiantOneHandActionWithLegTurn, GiantAttackWithAS)
public:
    explicit GiantOneHandActionWithLegTurn(const InitArg& arg);
    ~GiantOneHandActionWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const float* mTraceLRAngleMax_s{};
    // static_param at offset 0x140
    const float* mTraceLRAngleMin_s{};
    // static_param at offset 0x148
    const float* mTraceDistFar_s{};
    // static_param at offset 0x150
    const float* mTraceDistNear_s{};
    // static_param at offset 0x158
    sead::SafeString mShoulderBoneName_s{};
    // static_param at offset 0x168
    const sead::Vector3f* mRotOffsetMin_s{};
    // static_param at offset 0x170
    const sead::Vector3f* mRotOffsetMax_s{};
    // static_param at offset 0x178
    const sead::Vector3f* mBaseTargetPos_s{};
};

}  // namespace uking::action
