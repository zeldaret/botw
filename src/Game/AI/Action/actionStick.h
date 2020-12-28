#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Stick : public ActionEx {
    SEAD_RTTI_OVERRIDE(Stick, ActionEx)
public:
    explicit Stick(const InitArg& arg);
    ~Stick() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
