#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordTornadoAttack : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossLswordTornadoAttack, ksys::act::ai::Action)
public:
    explicit SiteBossLswordTornadoAttack(const InitArg& arg);
    ~SiteBossLswordTornadoAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mEndTime_s{};
    // static_param at offset 0x28
    const float* mVacuumAcc_s{};
    // static_param at offset 0x30
    const float* mVacuumMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mVacuumAngle_s{};
    // static_param at offset 0x40
    const float* mVacuumBaseWeight_s{};
};

}  // namespace uking::action
