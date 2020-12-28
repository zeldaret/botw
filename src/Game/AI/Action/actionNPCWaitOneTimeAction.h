#pragma once

#include "Game/AI/Action/actionNPCWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NPCWaitOneTimeAction : public NPCWait {
    SEAD_RTTI_OVERRIDE(NPCWaitOneTimeAction, NPCWait)
public:
    explicit NPCWaitOneTimeAction(const InitArg& arg);
    ~NPCWaitOneTimeAction() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
