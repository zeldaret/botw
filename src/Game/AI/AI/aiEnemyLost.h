#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyLost : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyLost, ksys::act::ai::Ai)
public:
    explicit EnemyLost(const InitArg& arg);
    ~EnemyLost() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRailCheckInterval_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x48
    const float* mForceReturnNoCameraRad_s{};
    // static_param at offset 0x50
    const bool* mSealForceReturn_s{};
};

}  // namespace uking::ai
