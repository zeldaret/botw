#pragma once

#include "Game/AI/AI/aiNonPlayerHorseRide.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyHorseRide : public NonPlayerHorseRide {
    SEAD_RTTI_OVERRIDE(EnemyHorseRide, NonPlayerHorseRide)
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
