#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterSurfaceMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterSurfaceMove, ksys::act::ai::Action)
public:
    explicit WaterSurfaceMove(const InitArg& arg);
    ~WaterSurfaceMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mSpeed_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
