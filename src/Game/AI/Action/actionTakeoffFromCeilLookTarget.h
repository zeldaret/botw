#pragma once

#include "Game/AI/Action/actionTakeoffFromCeilLook.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TakeoffFromCeilLookTarget : public TakeoffFromCeilLook {
    SEAD_RTTI_OVERRIDE(TakeoffFromCeilLookTarget, TakeoffFromCeilLook)
public:
    explicit TakeoffFromCeilLookTarget(const InitArg& arg);
    ~TakeoffFromCeilLookTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
