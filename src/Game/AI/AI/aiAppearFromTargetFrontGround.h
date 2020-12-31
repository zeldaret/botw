#pragma once

#include "Game/AI/AI/aiAppearNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearFromTargetFrontGround : public AppearNearTarget {
    SEAD_RTTI_OVERRIDE(AppearFromTargetFrontGround, AppearNearTarget)
public:
    explicit AppearFromTargetFrontGround(const InitArg& arg);
    ~AppearFromTargetFrontGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
