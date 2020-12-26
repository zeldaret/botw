#pragma once

#include "Game/AI/Action/actionWillBallAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WillBallAvoidCenterDist : public WillBallAction {
    SEAD_RTTI_OVERRIDE(WillBallAvoidCenterDist, WillBallAction)
public:
    explicit WillBallAvoidCenterDist(const InitArg& arg);
    ~WillBallAvoidCenterDist() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mDist_s{};
    // static_param at offset 0xa0
    const float* mMaxDist_s{};
    // static_param at offset 0xa8
    const float* mMiddleDist_s{};
    // dynamic_param at offset 0xb0
    sead::Vector3f* mCenterPos_d{};
};

}  // namespace uking::action
