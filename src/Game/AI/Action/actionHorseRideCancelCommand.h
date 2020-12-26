#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideCancelCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideCancelCommand, HorseRideCommand)
public:
    explicit HorseRideCancelCommand(const InitArg& arg);
    ~HorseRideCancelCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
