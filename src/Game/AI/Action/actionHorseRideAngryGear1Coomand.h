#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideAngryGear1Coomand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideAngryGear1Coomand, HorseRideCommand)
public:
    explicit HorseRideAngryGear1Coomand(const InitArg& arg);
    ~HorseRideAngryGear1Coomand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
