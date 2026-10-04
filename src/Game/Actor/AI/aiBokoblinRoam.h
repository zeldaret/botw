#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinRoam, ksys::act::ai::Ai)
public:
    explicit BokoblinRoam(const InitArg& arg);
    ~BokoblinRoam() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFreeIntervalMin_s{};
    // static_param at offset 0x40
    const int* mFreeIntervalMax_s{};
    // static_param at offset 0x48
    const int* mFreePer_s{};
    // static_param at offset 0x50
    const int* mMoveIntervalMin_s{};
    // static_param at offset 0x58
    const int* mMoveIntervalMax_s{};
    // static_param at offset 0x60
    const int* mNoMoveTime_s{};
    // static_param at offset 0x68
    const int* mNoSpAttackMoveTime_s{};
    // static_param at offset 0x70
    const int* mSpAttackServiceTime_s{};
    // static_param at offset 0x78
    const float* mTerritory_s{};
    // static_param at offset 0x80
    const float* mTargetDistMin_s{};
    // static_param at offset 0x88
    const float* mTargetDistMax_s{};
    // static_param at offset 0x90
    const float* mSpAttackServiceDist_s{};
    // static_param at offset 0x98
    const float* mSpAttackServiceAngle_s{};
    // dynamic_param at offset 0xa0
    sead::Vector3f* mCentralPos_d{};
    // static_param at offset 0xa8
    const float* mTurnCheckDist_s{};
    // static_param at offset 0xb0
    const float* mTurnCheckHeight_s{};
};

}  // namespace uking::ai
