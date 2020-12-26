#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChargeCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChargeCommand, HorseRideMoveCommand)
public:
    explicit HorseRideChargeCommand(const InitArg& arg);
    ~HorseRideChargeCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
