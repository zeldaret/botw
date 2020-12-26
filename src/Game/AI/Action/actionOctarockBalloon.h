#pragma once

#include "Game/AI/Action/actionOctarockBalloonBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OctarockBalloon : public OctarockBalloonBase {
    SEAD_RTTI_OVERRIDE(OctarockBalloon, OctarockBalloonBase)
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
