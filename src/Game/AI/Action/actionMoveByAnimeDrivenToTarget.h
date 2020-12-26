#pragma once

#include "Game/AI/Action/actionMoveByAnimeDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveByAnimeDrivenToTarget : public MoveByAnimeDriven {
    SEAD_RTTI_OVERRIDE(MoveByAnimeDrivenToTarget, MoveByAnimeDriven)
public:
    explicit MoveByAnimeDrivenToTarget(const InitArg& arg);
    ~MoveByAnimeDrivenToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x58
    const float* mAnimRotateMax_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
