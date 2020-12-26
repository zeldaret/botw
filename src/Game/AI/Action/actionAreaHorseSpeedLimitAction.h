#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaHorseSpeedLimitAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(AreaHorseSpeedLimitAction, AreaTagAction)
public:
    explicit AreaHorseSpeedLimitAction(const InitArg& arg);
    ~AreaHorseSpeedLimitAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
