#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Notice : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(Notice, ActionWithAS)
public:
    bool isChangeable() const override { return false; }
    explicit Notice(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
};

}  // namespace uking::action
