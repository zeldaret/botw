#pragma once

#include "Game/Actor/Action/actionWillBallBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WillBallAttack : public WillBallBase {
    SEAD_RTTI_OVERRIDE(WillBallAttack, WillBallBase)
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
