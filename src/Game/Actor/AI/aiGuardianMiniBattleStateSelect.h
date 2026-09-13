#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBattleStateSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniBattleStateSelect, ksys::act::ai::Ai)
public:
    explicit GuardianMiniBattleStateSelect(const InitArg& arg);
    ~GuardianMiniBattleStateSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSecondLifeRatio_s{};
    // static_param at offset 0x40
    const float* mFinalLifeRatio_s{};
    // static_param at offset 0x48
    const bool* mIsEnterOnly_s{};
};

}  // namespace uking::ai
