#pragma once

#include "Game/AI/AI/aiReflectableThrown.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ReflectableIgnitedThrown : public ReflectableThrown {
    SEAD_RTTI_OVERRIDE(ReflectableIgnitedThrown, ReflectableThrown)
public:
    explicit ReflectableIgnitedThrown(const InitArg& arg);
    ~ReflectableIgnitedThrown() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
