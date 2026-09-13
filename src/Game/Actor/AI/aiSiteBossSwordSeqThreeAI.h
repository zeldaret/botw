#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossSwordSeqThreeAI : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SiteBossSwordSeqThreeAI, ksys::act::ai::Ai)
public:
    explicit SiteBossSwordSeqThreeAI(const InitArg& arg);
    ~SiteBossSwordSeqThreeAI() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsSkipLastAction_s{};
    // dynamic_param at offset 0x40
    bool* mIsResetEndTime_d{};
    // dynamic_param at offset 0x48
    bool* mIsAttackPatternFixed_d{};
    // dynamic_param at offset 0x50
    bool* mIsNoCharge_d{};
    // dynamic_param at offset 0x58
    bool* mIsRestart_d{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mOldTargetPos_d{};
};

}  // namespace uking::ai
