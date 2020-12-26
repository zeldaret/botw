#pragma once

#include "Game/AI/Action/actionSwimRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimTurnBase : public SwimRotateBase {
    SEAD_RTTI_OVERRIDE(SwimTurnBase, SwimRotateBase)
public:
    explicit SwimTurnBase(const InitArg& arg);
    ~SwimTurnBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mFinRotate_s{};
    // dynamic_param at offset 0xb0
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
