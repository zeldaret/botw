#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonBeastHeadBarrier : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonBeastHeadBarrier, ksys::act::ai::Action)
public:
    explicit ForkGanonBeastHeadBarrier(const InitArg& arg);
    ~ForkGanonBeastHeadBarrier() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mBarrierRad_s{};
    // static_param at offset 0x28
    const float* mBarrierFront_s{};
    // static_param at offset 0x30
    const float* mBarrierBack_s{};
    // static_param at offset 0x38
    const float* mBarrierHeight_s{};
    // static_param at offset 0x40
    const float* mBarrierHeightMax_s{};
};

}  // namespace uking::action
