#pragma once

#include "Game/AI/Action/actionForkAnimDriveMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkAnimDriveTurn : public ForkAnimDriveMove {
    SEAD_RTTI_OVERRIDE(ForkAnimDriveTurn, ForkAnimDriveMove)
public:
    explicit ForkAnimDriveTurn(const InitArg& arg);
    ~ForkAnimDriveTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x38
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
