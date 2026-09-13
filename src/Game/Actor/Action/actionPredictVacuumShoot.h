#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PredictVacuumShoot : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PredictVacuumShoot, ksys::act::ai::Action)
public:
    explicit PredictVacuumShoot(const InitArg& arg);
    ~PredictVacuumShoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mAngReduceRatio_s{};
    // static_param at offset 0x30
    const float* mRotSpd_s{};
    // static_param at offset 0x38
    const bool* mIsReuseBullet_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
