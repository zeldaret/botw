#pragma once

#include "Game/Actor/Action/actionHorseRideSetGearCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChargeCommand : public HorseRideSetGearCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChargeCommand, HorseRideSetGearCommand)
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
