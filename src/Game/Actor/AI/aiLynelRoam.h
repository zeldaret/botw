#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelRoam, ksys::act::ai::Ai)
public:
    explicit LynelRoam(const InitArg& arg);
    ~LynelRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
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
    const int* mRepathTime_s{};
    // static_param at offset 0x80
    const float* mTerritory_s{};
    // static_param at offset 0x88
    const float* mTargetDistMin_s{};
    // static_param at offset 0x90
    const float* mTargetDistMax_s{};
    // static_param at offset 0x98
    const float* mSpAttackServiceDist_s{};
    // static_param at offset 0xa0
    const float* mSpAttackServiceAngle_s{};
    // dynamic_param at offset 0xa8
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
