#pragma once

#include "Game/Actor/Horse/AI/aiRideHorseNonPlayer.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyHorseRide : public RideHorseNonPlayer {
    SEAD_RTTI_OVERRIDE(EnemyHorseRide, RideHorseNonPlayer)
public:
    explicit EnemyHorseRide(const InitArg& arg);
    ~EnemyHorseRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const int* mUpperBodyASSlot_s{};
    // static_param at offset 0xe8
    const int* mLowerBodyASSlot_s{};
};

}  // namespace uking::ai
