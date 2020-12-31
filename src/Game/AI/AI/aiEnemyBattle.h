#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBattle, ksys::act::ai::Ai)
public:
    explicit EnemyBattle(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mRetFrmGrdAtkTimer_s{};
    // static_param at offset 0x40
    const int* mRetFrmGrdAtkPrcTimer_s{};
    // static_param at offset 0x48
    const int* mRetFrmDmgAtkTimer_s{};
    // static_param at offset 0x50
    const int* mGlobalNoAtkTime_s{};
    // static_param at offset 0x58
    const int* mGlobalNoAtkTimeRnd_s{};
    // static_param at offset 0x60
    const float* mAttackAngle_s{};
    // static_param at offset 0x68
    const float* mAttackIntervalIntensity_s{};
    // static_param at offset 0x70
    const float* mDisplayCheckRadius_s{};
    // static_param at offset 0x78
    const bool* mIsUpdateNoticeState_s{};
    // static_param at offset 0x80
    const bool* mIsCheckLineReachable_s{};
};

}  // namespace uking::ai
