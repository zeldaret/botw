#pragma once

#include "Game/Actor/Action/actionHorseRideBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideSearch : public HorseRideBase {
    SEAD_RTTI_OVERRIDE(HorseRideSearch, HorseRideBase)
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
