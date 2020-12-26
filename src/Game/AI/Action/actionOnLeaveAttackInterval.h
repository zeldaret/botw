#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnLeaveAttackInterval : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OnLeaveAttackInterval, ksys::act::ai::Action)
public:
    explicit OnLeaveAttackInterval(const InitArg& arg);
    ~OnLeaveAttackInterval() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
