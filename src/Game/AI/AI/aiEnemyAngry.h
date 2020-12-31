#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyAngry : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyAngry, ksys::act::ai::Ai)
public:
    explicit EnemyAngry(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mTurnAng_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
