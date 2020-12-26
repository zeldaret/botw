#pragma once

#include "Game/AI/Action/actionMoveToTargetBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveToTarget : public MoveToTargetBase {
    SEAD_RTTI_OVERRIDE(MoveToTarget, MoveToTargetBase)
public:
    explicit MoveToTarget(const InitArg& arg);
    ~MoveToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x40
    const float* mRailMoveSpeed_m{};
};

}  // namespace uking::action
