#pragma once

#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDistWithTgtBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MultiVacuumRotScaleTimeByDistWithTgt : public MultiVacuumRotScaleTimeByDistWithTgtBase {
    SEAD_RTTI_OVERRIDE(MultiVacuumRotScaleTimeByDistWithTgt,
                       MultiVacuumRotScaleTimeByDistWithTgtBase)
public:
    explicit MultiVacuumRotScaleTimeByDistWithTgt(const InitArg& arg);
    ~MultiVacuumRotScaleTimeByDistWithTgt() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x1c0
    const float* mRotSpd_s{};
    // static_param at offset 0x1c8
    const float* mPosReduceRatio_s{};
    // dynamic_param at offset 0x1d0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
