#pragma once

#include "Game/AI/Action/actionRagdoll.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BlownOff : public Ragdoll {
    SEAD_RTTI_OVERRIDE(BlownOff, Ragdoll)
public:
    explicit BlownOff(const InitArg& arg);
    ~BlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x118
    const int* mAddTime_s{};
    // static_param at offset 0x120
    const float* mLifeReflexRatio_s{};
    // static_param at offset 0x128
    const float* mImpulseRatio_s{};
};

}  // namespace uking::action
