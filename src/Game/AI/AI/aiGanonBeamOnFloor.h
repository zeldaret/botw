#pragma once

#include "Game/AI/AI/aiLastBossShootNormalArrowRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonBeamOnFloor : public LastBossShootNormalArrowRoot {
    SEAD_RTTI_OVERRIDE(GanonBeamOnFloor, LastBossShootNormalArrowRoot)
public:
    explicit GanonBeamOnFloor(const InitArg& arg);
    ~GanonBeamOnFloor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x260
    const float* mTurnStartAng_s{};
    // static_param at offset 0x268
    const float* mKeepMinDist_s{};
    // static_param at offset 0x270
    const float* mTurnRate_s{};
    // static_param at offset 0x278
    sead::SafeString mWalkAS_s{};
    // static_param at offset 0x288
    sead::SafeString mTurnAS_s{};
};

}  // namespace uking::ai
