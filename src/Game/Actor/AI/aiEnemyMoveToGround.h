#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyMoveToGround : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyMoveToGround, ksys::act::ai::Ai)
public:
    explicit EnemyMoveToGround(const InitArg& arg);
    ~EnemyMoveToGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRetryTime_s{};
    // static_param at offset 0x40
    const float* mAreaThreshold_s{};
    // static_param at offset 0x48
    const float* mSearchRadius_s{};
};

}  // namespace uking::ai
