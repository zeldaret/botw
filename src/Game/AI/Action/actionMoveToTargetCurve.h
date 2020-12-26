#pragma once

#include "Game/AI/Action/actionMoveToTargetCurveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveToTargetCurve : public MoveToTargetCurveBase {
    SEAD_RTTI_OVERRIDE(MoveToTargetCurve, MoveToTargetCurveBase)
public:
    explicit MoveToTargetCurve(const InitArg& arg);
    ~MoveToTargetCurve() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x68
    const sead::Vector3f* mTargetPosition_m{};
};

}  // namespace uking::action
