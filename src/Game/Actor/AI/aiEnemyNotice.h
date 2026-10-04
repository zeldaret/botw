#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyNotice : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyNotice, ksys::act::ai::Ai)
public:
    explicit EnemyNotice(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x40
    const float* mTurnStartAngle_s{};
};

}  // namespace uking::ai
