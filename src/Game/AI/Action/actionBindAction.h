#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BindAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BindAction, ksys::act::ai::Action)
public:
    explicit BindAction(const InitArg& arg);
    ~BindAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
