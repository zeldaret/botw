#pragma once

#include "Game/AI/Action/actionAreaObserveActorAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FlyingBalloonObserverTag : public AreaObserveActorAction {
    SEAD_RTTI_OVERRIDE(FlyingBalloonObserverTag, AreaObserveActorAction)
public:
    explicit FlyingBalloonObserverTag(const InitArg& arg);
    ~FlyingBalloonObserverTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
