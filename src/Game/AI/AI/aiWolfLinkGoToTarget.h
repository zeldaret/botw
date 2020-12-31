#pragma once

#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkGoToTarget : public HorseFollow {
    SEAD_RTTI_OVERRIDE(WolfLinkGoToTarget, HorseFollow)
public:
    explicit WolfLinkGoToTarget(const InitArg& arg);
    ~WolfLinkGoToTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
