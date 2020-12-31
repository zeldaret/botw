#pragma once

#include "Game/AI/AI/aiAppearNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearFromTargetFrontAfterChase : public AppearNearTarget {
    SEAD_RTTI_OVERRIDE(AppearFromTargetFrontAfterChase, AppearNearTarget)
public:
    explicit AppearFromTargetFrontAfterChase(const InitArg& arg);
    ~AppearFromTargetFrontAfterChase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x90
    const float* mAppearDist_s{};
};

}  // namespace uking::ai
