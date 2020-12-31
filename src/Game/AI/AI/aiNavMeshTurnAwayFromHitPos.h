#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NavMeshTurnAwayFromHitPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NavMeshTurnAwayFromHitPos, ksys::act::ai::Ai)
public:
    explicit NavMeshTurnAwayFromHitPos(const InitArg& arg);
    ~NavMeshTurnAwayFromHitPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNumLOSCheckMax_s{};
    // static_param at offset 0x40
    const float* mLOSCheckLength_s{};
    // static_param at offset 0x48
    const bool* mMoveToSafePosAfterTurn_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mHitPos_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
