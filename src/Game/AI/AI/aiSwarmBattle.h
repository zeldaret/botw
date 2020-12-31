#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwarmBattle, ksys::act::ai::Ai)
public:
    explicit SwarmBattle(const InitArg& arg);
    ~SwarmBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFailedRiseHeight_s{};
    // static_param at offset 0x40
    const float* mRiseFailedMoveDist_s{};
    // static_param at offset 0x48
    const float* mAttackIntervalIntensity_s{};
};

}  // namespace uking::ai
