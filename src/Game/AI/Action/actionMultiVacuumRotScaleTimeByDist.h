#pragma once

#include "Game/AI/Action/actionMultiVacuumRotScaleTimeByDistWithTgt.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MultiVacuumRotScaleTimeByDist : public MultiVacuumRotScaleTimeByDistWithTgt {
    SEAD_RTTI_OVERRIDE(MultiVacuumRotScaleTimeByDist, MultiVacuumRotScaleTimeByDistWithTgt)
public:
    explicit MultiVacuumRotScaleTimeByDist(const InitArg& arg);
    ~MultiVacuumRotScaleTimeByDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x200
    const float* mMaxTimeDist_s{};
};

}  // namespace uking::action
