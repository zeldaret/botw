#pragma once

#include "Game/Actor/Action/actionHorseRideOneTimeCommandBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideCommand : public HorseRideOneTimeCommandBase {
    SEAD_RTTI_OVERRIDE(HorseRideCommand, HorseRideOneTimeCommandBase)
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
