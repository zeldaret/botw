#pragma once

#include "Game/Actor/AI/aiAppearFromTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearFromTargetFrontAfterChase : public AppearFromTarget {
    SEAD_RTTI_OVERRIDE(AppearFromTargetFrontAfterChase, AppearFromTarget)
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
