#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act::ai {

class DummyAction : public Action {
    SEAD_RTTI_OVERRIDE(DummyAction, Action)
public:
    explicit DummyAction(const InitArg& arg);
    void enter_(InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace ksys::act::ai
