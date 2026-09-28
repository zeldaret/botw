#pragma once

#include "Game/Actor/Action/actionHorseRideBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideWait : public HorseRideBase {
    SEAD_RTTI_OVERRIDE(HorseRideWait, HorseRideBase)
public:
    explicit HorseRideWait(const InitArg& arg);
    ~HorseRideWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mTime_s{};
    // static_param at offset 0x38
    const int* mTimeRand_s{};
};

}  // namespace uking::action
