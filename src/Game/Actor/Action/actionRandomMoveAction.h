#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RandomMoveAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RandomMoveAction, ksys::act::ai::Action)
public:
    explicit RandomMoveAction(const InitArg& arg);
    ~RandomMoveAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mIsSuccessWhenGoalReached_s{};
};

}  // namespace uking::action
