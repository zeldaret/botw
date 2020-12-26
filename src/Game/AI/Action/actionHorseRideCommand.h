#pragma once

#include "Game/AI/Action/actionHorseRideCommandBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideCommand : public HorseRideCommandBase {
    SEAD_RTTI_OVERRIDE(HorseRideCommand, HorseRideCommandBase)
public:
    explicit HorseRideCommand(const InitArg& arg);
    ~HorseRideCommand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mCommandTiming_s{};
};

}  // namespace uking::action
