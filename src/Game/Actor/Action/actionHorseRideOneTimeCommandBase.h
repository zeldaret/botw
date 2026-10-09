#pragma once

#include "Game/Actor/Action/actionHorseRideLookWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideOneTimeCommandBase : public HorseRideLookWait {
    SEAD_RTTI_OVERRIDE(HorseRideOneTimeCommandBase, HorseRideLookWait)
public:
    explicit HorseRideOneTimeCommandBase(const InitArg& arg);
    ~HorseRideOneTimeCommandBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
