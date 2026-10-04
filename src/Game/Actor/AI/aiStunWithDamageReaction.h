#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StunWithDamageReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StunWithDamageReaction, ksys::act::ai::Ai)
public:
    explicit StunWithDamageReaction(const InitArg& arg);
    ~StunWithDamageReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTimer_s{};
    // static_param at offset 0x40
    const float* mForceEndLifeRatio_s{};
};

}  // namespace uking::ai
