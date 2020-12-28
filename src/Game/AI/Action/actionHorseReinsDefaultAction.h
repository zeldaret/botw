#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseReinsDefaultAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(HorseReinsDefaultAction, ksys::act::ai::Action)
public:
    explicit HorseReinsDefaultAction(const InitArg& arg);
    ~HorseReinsDefaultAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
