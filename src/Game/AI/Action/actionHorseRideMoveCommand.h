#pragma once

#include "Game/AI/Action/actionHorseRideCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideMoveCommand : public HorseRideCommand {
    SEAD_RTTI_OVERRIDE(HorseRideMoveCommand, HorseRideCommand)
public:
    explicit HorseRideMoveCommand(const InitArg& arg);
    ~HorseRideMoveCommand() override;

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
