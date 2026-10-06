#pragma once

#include "Game/Actor/Action/actionHorseRideSetGearCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChaseCommand : public HorseRideSetGearCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChaseCommand, HorseRideSetGearCommand)
public:
    explicit HorseRideChaseCommand(const InitArg& arg);
    ~HorseRideChaseCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x98
    const float* mChaseKeepDist_s{};
};

}  // namespace uking::action
