#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaFireObserveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaFireObserveBase, ksys::act::ai::Action)
public:
    explicit AreaFireObserveBase(const InitArg& arg);
    ~AreaFireObserveBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
