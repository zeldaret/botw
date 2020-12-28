#pragma once

#include "Game/AI/Action/actionChemicalPhysBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RodMagicPhysBall : public ChemicalPhysBall {
    SEAD_RTTI_OVERRIDE(RodMagicPhysBall, ChemicalPhysBall)
public:
    explicit RodMagicPhysBall(const InitArg& arg);
    ~RodMagicPhysBall() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb8
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0xc8
    const int* mChemicalType_s{};
    // static_param at offset 0xd0
    const float* mBgCheckHeight_s{};
};

}  // namespace uking::action
