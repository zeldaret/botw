#pragma once

#include "Game/Actor/Action/actionOneTimeWaterFloatStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WaterFloatElectricParalysis : public OneTimeWaterFloatStopASPlay {
    SEAD_RTTI_OVERRIDE(WaterFloatElectricParalysis, OneTimeWaterFloatStopASPlay)
public:
    explicit WaterFloatElectricParalysis(const InitArg& arg);
    ~WaterFloatElectricParalysis() override;

    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
