#pragma once

#include "Game/AI/Action/actionRodMagicPhysBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RodMagicPhysBallDivision : public RodMagicPhysBall {
    SEAD_RTTI_OVERRIDE(RodMagicPhysBallDivision, RodMagicPhysBall)
public:
    explicit RodMagicPhysBallDivision(const InitArg& arg);
    ~RodMagicPhysBallDivision() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x1b8
    const int* mDivNum_s{};
    // static_param at offset 0x1c0
    const float* mDivDist_s{};
    // static_param at offset 0x1c8
    const float* mDivAngle_s{};
    // static_param at offset 0x1d0
    sead::SafeString mChildName_s{};
};

}  // namespace uking::action
