#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterSurfaceModelOnly : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WaterSurfaceModelOnly, ksys::act::ai::Action)
public:
    explicit WaterSurfaceModelOnly(const InitArg& arg);
    ~WaterSurfaceModelOnly() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const float* mFlowSpeedFactor_m{};
};

}  // namespace uking::action
