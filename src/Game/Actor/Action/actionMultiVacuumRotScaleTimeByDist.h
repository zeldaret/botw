#pragma once

#include "Game/Actor/Action/actionMultiVacuumRotBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MultiVacuumRotScaleTimeByDist : public MultiVacuumRotBase {
    SEAD_RTTI_OVERRIDE(MultiVacuumRotScaleTimeByDist, MultiVacuumRotBase)
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
