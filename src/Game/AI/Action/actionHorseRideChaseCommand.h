#pragma once

#include "Game/AI/Action/actionHorseRideMoveCommand.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideChaseCommand : public HorseRideMoveCommand {
    SEAD_RTTI_OVERRIDE(HorseRideChaseCommand, HorseRideMoveCommand)
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
