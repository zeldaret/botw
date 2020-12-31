#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkNormalRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkNormalRoot, ksys::act::ai::Ai)
public:
    explicit WolfLinkNormalRoot(const InitArg& arg);
    ~WolfLinkNormalRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mShiekSensorLeadDistance_s{};
    // static_param at offset 0x40
    const float* mShiekSensorGoalTolerance_s{};
    // static_param at offset 0x48
    const float* mShiekSensorTargetFowardOffset_s{};
    // static_param at offset 0x50
    const float* mBattleAggressionRange_s{};
    // static_param at offset 0x58
    const float* mHowlAtEnemyRange_s{};
    // static_param at offset 0x60
    const float* mUtilityWantsToHunt_s{};
    // static_param at offset 0x68
    const float* mWarpToPlayerDistance_s{};
};

}  // namespace uking::ai
