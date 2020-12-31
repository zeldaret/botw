#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyWarnNoticeSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyWarnNoticeSelect, ksys::act::ai::Ai)
public:
    explicit EnemyWarnNoticeSelect(const InitArg& arg);
    ~EnemyWarnNoticeSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWarnNoticeTime_s{};
    // static_param at offset 0x40
    const int* mWarnNoticeTimeRnd_s{};
    // static_param at offset 0x48
    const int* mWarnBlinkTime_s{};
    // static_param at offset 0x50
    const int* mLostCounter_s{};
    // static_param at offset 0x58
    const int* mPenaltyStair2Num_s{};
    // static_param at offset 0x60
    const float* mMaxCountUp_s{};
    // static_param at offset 0x68
    const float* mPenalty_s{};
    // static_param at offset 0x70
    const int* mNoPenaltyNum_s{};
    // static_param at offset 0x78
    const bool* mIsSight_s{};
    // static_param at offset 0x80
    const bool* mIsWorry_s{};
    // dynamic_param at offset 0x88
    bool* mForceNotice_d{};
    // dynamic_param at offset 0x90
    ksys::act::BaseProcLink* mTargetActor_d{};
    // aitree_variable at offset 0x98
    bool* mIsTrgChangeUnderWaterState_a{};
};

}  // namespace uking::ai
