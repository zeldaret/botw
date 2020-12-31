#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FlyingEnemyKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FlyingEnemyKeepMove, ksys::act::ai::Ai)
public:
    explicit FlyingEnemyKeepMove(const InitArg& arg);
    ~FlyingEnemyKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mLostDistance_s{};
    // static_param at offset 0x40
    const float* mAngleRange_s{};
    // static_param at offset 0x48
    const float* mSpaceDistance_s{};
    // static_param at offset 0x50
    const float* mNearDist_s{};
    // static_param at offset 0x58
    const float* mFarDist_s{};
    // static_param at offset 0x60
    const float* mBaseDist_s{};
    // static_param at offset 0x68
    const float* mBaseHeight_s{};
    // static_param at offset 0x70
    const float* mLowHeight_s{};
    // static_param at offset 0x78
    const float* mHighHeight_s{};
};

}  // namespace uking::ai
