#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRangeKeepSwimMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRangeKeepSwimMove, ksys::act::ai::Ai)
public:
    explicit EnemyRangeKeepSwimMove(const InitArg& arg);
    ~EnemyRangeKeepSwimMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const int* mTime_s{};
    // static_param at offset 0x48
    const float* mCloseDist_s{};
    // static_param at offset 0x50
    const float* mFarDist_s{};
    // static_param at offset 0x58
    const float* mOutDist_s{};
    // static_param at offset 0x60
    const float* mBaseDist_s{};
    // static_param at offset 0x68
    const float* mSpaceDist_s{};
    // static_param at offset 0x70
    const bool* mIsCheckCliff_s{};
};

}  // namespace uking::ai
