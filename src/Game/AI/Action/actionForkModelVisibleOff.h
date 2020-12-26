#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkModelVisibleOff : public Fork {
    SEAD_RTTI_OVERRIDE(ForkModelVisibleOff, Fork)
public:
    explicit ForkModelVisibleOff(const InitArg& arg);
    ~ForkModelVisibleOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mUseFadeIn_s{};
    // static_param at offset 0x38
    const bool* mUseASEvent_s{};
};

}  // namespace uking::action
