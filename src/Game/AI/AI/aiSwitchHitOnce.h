#pragma once

#include "Game/AI/AI/aiSwitchHit.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwitchHitOnce : public SwitchHit {
    SEAD_RTTI_OVERRIDE(SwitchHitOnce, SwitchHit)
public:
    explicit SwitchHitOnce(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::ai
