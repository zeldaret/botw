#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaRecreateActorAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaRecreateActorAction, AreaTagAction)
public:
    explicit AreaRecreateActorAction(const InitArg& arg);
    ~AreaRecreateActorAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
