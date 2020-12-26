#pragma once

#include "Game/AI/Action/actionHorseRideViewWait.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TimeredHorseRideViewWait : public HorseRideViewWait {
    SEAD_RTTI_OVERRIDE(TimeredHorseRideViewWait, HorseRideViewWait)
public:
    explicit TimeredHorseRideViewWait(const InitArg& arg);
    ~TimeredHorseRideViewWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x50
    const int* mTime_s{};
    // static_param at offset 0x58
    const int* mTimeRand_s{};
};

}  // namespace uking::action
