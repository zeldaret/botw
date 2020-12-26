#pragma once

#include "Game/AI/Action/actionDie.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DieHomeRun : public Die {
    SEAD_RTTI_OVERRIDE(DieHomeRun, Die)
public:
    explicit DieHomeRun(const InitArg& arg);
    ~DieHomeRun() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x160
    const float* mToStarHeight_s{};
    // static_param at offset 0x168
    const float* mFallHeight_s{};
};

}  // namespace uking::action
