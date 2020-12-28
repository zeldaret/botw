#pragma once

#include "Game/AI/Action/actionWaitBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Wait : public WaitBase {
    SEAD_RTTI_OVERRIDE(Wait, WaitBase)
public:
    explicit Wait(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
