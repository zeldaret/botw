#pragma once

#include "Game/AI/Action/actionHorseRide.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRideOneTimeASPlay : public HorseRide {
    SEAD_RTTI_OVERRIDE(HorseRideOneTimeASPlay, HorseRide)
public:
    explicit HorseRideOneTimeASPlay(const InitArg& arg);
    ~HorseRideOneTimeASPlay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const bool* mIgnoreSameAS_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
