#pragma once

#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkModelFadeOut : public Fork {
    SEAD_RTTI_OVERRIDE(ForkModelFadeOut, Fork)
public:
    explicit ForkModelFadeOut(const InitArg& arg);
    ~ForkModelFadeOut() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
