#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoVisibleOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoVisibleOff, ksys::act::ai::Action)
public:
    explicit DemoVisibleOff(const InitArg& arg);
    ~DemoVisibleOff() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
};

}  // namespace uking::action
