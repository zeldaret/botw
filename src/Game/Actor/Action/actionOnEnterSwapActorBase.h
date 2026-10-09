#pragma once

#include "Game/Actor/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnEnterSwapActorBase : public Fork {
    SEAD_RTTI_OVERRIDE(OnEnterSwapActorBase, Fork)
public:
    explicit OnEnterSwapActorBase(const InitArg& arg);
    ~OnEnterSwapActorBase() override;

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
