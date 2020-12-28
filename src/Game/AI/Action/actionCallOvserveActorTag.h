#pragma once

#include "Game/AI/Action/actionAreaObserveActorAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CallOvserveActorTag : public AreaObserveActorAction {
    SEAD_RTTI_OVERRIDE(CallOvserveActorTag, AreaObserveActorAction)
public:
    explicit CallOvserveActorTag(const InitArg& arg);
    ~CallOvserveActorTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
