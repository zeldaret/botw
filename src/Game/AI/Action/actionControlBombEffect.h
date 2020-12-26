#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ControlBombEffect : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(ControlBombEffect, AreaTagAction)
public:
    explicit ControlBombEffect(const InitArg& arg);
    ~ControlBombEffect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
