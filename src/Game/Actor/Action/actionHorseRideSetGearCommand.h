#pragma once

#include "Game/Actor/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideSetGearCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideSetGearCommand, HorseRideCommand)
public:
    explicit HorseRideSetGearCommand(const InitArg& arg);
    ~HorseRideSetGearCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x58
    const int* mGear_s{};
};

}  // namespace uking::action
