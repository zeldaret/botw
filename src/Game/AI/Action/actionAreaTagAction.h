#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaTagAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaTagAction, ksys::act::ai::Action)
public:
    explicit AreaTagAction(const InitArg& arg);
    ~AreaTagAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;

protected:
    void calc_() override;
};

}  // namespace uking::action
