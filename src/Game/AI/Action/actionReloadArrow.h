#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReloadArrow : public ActionEx {
    SEAD_RTTI_OVERRIDE(ReloadArrow, ActionEx)
public:
    explicit ReloadArrow(const InitArg& arg);
    ~ReloadArrow() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
