#pragma once

#include "Game/AI/Action/actionPreJumpAttack.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeredPreJumpAttack : public PreJumpAttack {
    SEAD_RTTI_OVERRIDE(TimeredPreJumpAttack, PreJumpAttack)
public:
    explicit TimeredPreJumpAttack(const InitArg& arg);
    ~TimeredPreJumpAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const int* mTime_s{};
    // static_param at offset 0xa0
    const int* mTimeRand_s{};
};

}  // namespace uking::action
