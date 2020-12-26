#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsFireDroneRailStop : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsFireDroneRailStop, ksys::act::ai::Action)
public:
    explicit RemainsFireDroneRailStop(const InitArg& arg);
    ~RemainsFireDroneRailStop() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mDynStopTime_d{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mDynStopPos_d{};
};

}  // namespace uking::action
