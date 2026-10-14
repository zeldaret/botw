#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaActionBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaActionBase, ksys::act::ai::Action)
public:
    explicit AreaActionBase(const InitArg& arg);
    ~AreaActionBase() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
