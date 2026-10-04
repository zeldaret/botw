#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRangeKeepMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRangeKeepMove, ksys::act::ai::Ai)
public:
    explicit EnemyRangeKeepMove(const InitArg& arg);
    ~EnemyRangeKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mRefPosVibrateCheckerForAI_a{};
    // aitree_variable at offset 0x40
    void* mRefVelRotVibrateCheckerforAI_a{};
    // static_param at offset 0x48
    const int* mWeaponIdx_s{};
    // static_param at offset 0x50
    const int* mBackTimeMin_s{};
    // static_param at offset 0x58
    const int* mBackTimeMax_s{};
    // static_param at offset 0x60
    const int* mLeaveTimerMin_s{};
    // static_param at offset 0x68
    const int* mLeaveTimerMax_s{};
    // static_param at offset 0x70
    const int* mPosVibrateFrame_s{};
    // static_param at offset 0x78
    const int* mRotVelVibrateFrame_s{};
    // static_param at offset 0x80
    const float* mCloseDist_s{};
    // static_param at offset 0x88
    const float* mFarDist_s{};
    // static_param at offset 0x90
    const float* mOutDist_s{};
    // static_param at offset 0x98
    const float* mBaseDist_s{};
    // static_param at offset 0xa0
    const float* mSpaceDist_s{};
    // static_param at offset 0xa8
    const float* mSpaceAngle_s{};
    // static_param at offset 0xb0
    const bool* mIsCheckBack_s{};
    // static_param at offset 0xb8
    const bool* mIsCheckReachable_s{};
    // static_param at offset 0xc0
    const float* mNoMoveDist_s{};
};

}  // namespace uking::ai
