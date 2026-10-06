#pragma once

#include "Game/Actor/AI/aiAppearFromTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AppearNearTargetOutOfScrnGnd : public AppearFromTarget {
    SEAD_RTTI_OVERRIDE(AppearNearTargetOutOfScrnGnd, AppearFromTarget)
public:
    explicit AppearNearTargetOutOfScrnGnd(const InitArg& arg);
    ~AppearNearTargetOutOfScrnGnd() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
