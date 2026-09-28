#pragma once

#include "Game/Actor/Action/actionBalloonRopeBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockBalloon : public BalloonRopeBase {
    SEAD_RTTI_OVERRIDE(OctarockBalloon, BalloonRopeBase)
public:
    explicit OctarockBalloon(const InitArg& arg);
    ~OctarockBalloon() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const float* mTargetScale_s{};
    // static_param at offset 0x140
    const float* mStartSignTimer_s{};
    // static_param at offset 0x148
    sead::SafeString mStartASName_s{};
    // static_param at offset 0x158
    sead::SafeString mSignASName_s{};
};

}  // namespace uking::action
