#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PlayerBarrierBlow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PlayerBarrierBlow, ksys::act::ai::Ai)
public:
    explicit PlayerBarrierBlow(const InitArg& arg);
    ~PlayerBarrierBlow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBlowRagdollTime_s{};
};

}  // namespace uking::ai
