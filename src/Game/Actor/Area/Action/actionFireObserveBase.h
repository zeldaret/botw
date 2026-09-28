#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FireObserveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FireObserveBase, ksys::act::ai::Action)
public:
    explicit FireObserveBase(const InitArg& arg);
    ~FireObserveBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
