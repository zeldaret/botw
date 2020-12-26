#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkOnEnterSwapDropTableActorBase : public Fork {
    SEAD_RTTI_OVERRIDE(ForkOnEnterSwapDropTableActorBase, Fork)
public:
    explicit ForkOnEnterSwapDropTableActorBase(const InitArg& arg);
    ~ForkOnEnterSwapDropTableActorBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mOnGroundPos_s{};
};

}  // namespace uking::action
