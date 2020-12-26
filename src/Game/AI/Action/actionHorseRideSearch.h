#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideSearch : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideSearch, HorseRide)
public:
    explicit HorseRideSearch(const InitArg& arg);
    ~HorseRideSearch() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
