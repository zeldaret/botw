#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRecognizeTargetBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRecognizeTargetBase, ksys::act::ai::Ai)
public:
    explicit EnemyRecognizeTargetBase(const InitArg& arg);
    ~EnemyRecognizeTargetBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const int* mWeaponIdx_s{};
    // static_param at offset 0x48
    const int* mCryInterval_s{};
    // static_param at offset 0x50
    const int* mRandomCryInterval_s{};
    // static_param at offset 0x58
    const int* mRandomCryIntervalMax_s{};
    // static_param at offset 0x60
    const float* mSpreadDist_s{};
    // static_param at offset 0x68
    const float* mNoCryDist_s{};
};

}  // namespace uking::ai
