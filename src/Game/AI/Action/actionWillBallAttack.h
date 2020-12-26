#pragma once

#include "Game/AI/Action/actionWillBallAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WillBallAttack : public WillBallAction {
    SEAD_RTTI_OVERRIDE(WillBallAttack, WillBallAction)
public:
    explicit WillBallAttack(const InitArg& arg);
    ~WillBallAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const int* mReactionLevel_s{};
    // static_param at offset 0xa0
    const bool* mIsAbleGuard_s{};
};

}  // namespace uking::action
