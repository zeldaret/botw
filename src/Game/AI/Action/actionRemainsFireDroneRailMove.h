#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsFireDroneRailMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsFireDroneRailMove, ksys::act::ai::Action)
public:
    explicit RemainsFireDroneRailMove(const InitArg& arg);
    ~RemainsFireDroneRailMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mNearDistance_s{};
    // dynamic_param at offset 0x28
    sead::Vector3f* mTargetPos_d{};
    // aitree_variable at offset 0x30
    float* mTargetSpeed_a{};
};

}  // namespace uking::action
