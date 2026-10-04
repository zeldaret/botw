#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GoronHeroDescendentRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GoronHeroDescendentRoot, ksys::act::ai::Ai)
public:
    explicit GoronHeroDescendentRoot(const InitArg& arg);
    ~GoronHeroDescendentRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mGuardEndDelayTime_s{};
    // static_param at offset 0x40
    const int* mWhistleReactTimeGo_s{};
    // static_param at offset 0x48
    const int* mWhistleReactTimeStop_s{};
    // static_param at offset 0x50
    const int* mAppearWaitTime_s{};
    // static_param at offset 0x58
    const float* mPlayerNearDist_s{};
    // static_param at offset 0x60
    const float* mPlayerLeaveDist_s{};
    // static_param at offset 0x68
    const float* mPlayerSeparateDist_s{};
    // static_param at offset 0x70
    sead::SafeString mFollowModeFlagName_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mPlayerFollowOffset_s{};
};

}  // namespace uking::ai
