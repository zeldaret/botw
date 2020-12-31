#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CalledEnemyMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CalledEnemyMove, ksys::act::ai::Ai)
public:
    explicit CalledEnemyMove(const InitArg& arg);
    ~CalledEnemyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLostDist_s{};
    // static_param at offset 0x40
    const float* mWaitDist_s{};
    // dynamic_param at offset 0x48
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
