#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideTurnCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideTurnCommand, HorseRideCommand)
public:
    explicit HorseRideTurnCommand(const InitArg& arg);
    ~HorseRideTurnCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
