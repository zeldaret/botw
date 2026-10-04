#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRiddenByEnemyAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRiddenByEnemyAI, ksys::act::ai::Ai)
public:
    explicit HorseRiddenByEnemyAI(const InitArg& arg);
    ~HorseRiddenByEnemyAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAngryASPeriods_s{};
    // static_param at offset 0x40
    const float* mFramesRetryNormalActionAtFailed_s{};
};

}  // namespace uking::ai
