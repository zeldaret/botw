#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LizalfosBreathAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LizalfosBreathAttack, ksys::act::ai::Ai)
public:
    explicit LizalfosBreathAttack(const InitArg& arg);
    ~LizalfosBreathAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMinAttackTimeForTired_s{};
    // static_param at offset 0x40
    const int* mMinTiredTime_s{};
    // static_param at offset 0x48
    const float* mTiredTimeRate_s{};
};

}  // namespace uking::ai
