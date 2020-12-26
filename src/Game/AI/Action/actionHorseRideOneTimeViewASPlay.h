#pragma once

#include "Game/AI/Action/actionHorseRideViewWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideOneTimeViewASPlay : public HorseRideViewWait {
    SEAD_RTTI_OVERRIDE(HorseRideOneTimeViewASPlay, HorseRideViewWait)
public:
    explicit HorseRideOneTimeViewASPlay(const InitArg& arg);
    ~HorseRideOneTimeViewASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
