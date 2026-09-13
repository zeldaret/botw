#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class KnockBackShock : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(KnockBackShock, ksys::act::ai::Action)
public:
    explicit KnockBackShock(const InitArg& arg);
    ~KnockBackShock() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mHitImpactForce_s{};
    // static_param at offset 0x28
    const float* mVelReduce_s{};
    // static_param at offset 0x30
    const float* mVelReduceOnGround_s{};
};

}  // namespace uking::action
