#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BombExplode : public ActionEx {
    SEAD_RTTI_OVERRIDE(BombExplode, ActionEx)
public:
    explicit BombExplode(const InitArg& arg);
    ~BombExplode() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
