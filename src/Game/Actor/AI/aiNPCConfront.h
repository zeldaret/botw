#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCConfront : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCConfront, ksys::act::ai::Ai)
public:
    explicit NPCConfront(const InitArg& arg);
    ~NPCConfront() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mCounterGuardCount_s{};
    // static_param at offset 0x40
    const float* mReleaseDistance_s{};
    // static_param at offset 0x48
    const float* mReleaseTime_s{};
    // static_param at offset 0x50
    const float* mCounterRate_s{};
    // static_param at offset 0x58
    const float* mDirectTurnAngle_s{};
    // dynamic_param at offset 0x60
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x68
    bool* mIsTimeOver_d{};
    // dynamic_param at offset 0x70
    bool* mIsSitting_d{};
    // dynamic_param at offset 0x78
    bool* mIsNeedUnEquipWeapon_d{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x88
    ksys::act::BaseProcLink* mTerrorEmitter_d{};
};

}  // namespace uking::ai
