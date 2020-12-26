#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideDynSetGearCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideDynSetGearCommand, HorseRideCommand)
public:
    explicit HorseRideDynSetGearCommand(const InitArg& arg);
    ~HorseRideDynSetGearCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x58
    int* mGear_d{};
};

}  // namespace uking::action
