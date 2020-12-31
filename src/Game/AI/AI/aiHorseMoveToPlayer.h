#pragma once

#include "Game/AI/AI/aiHorseFollow.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseMoveToPlayer : public HorseFollow {
    SEAD_RTTI_OVERRIDE(HorseMoveToPlayer, HorseFollow)
public:
    explicit HorseMoveToPlayer(const InitArg& arg);
    ~HorseMoveToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const float* mDistanceSuccessEndIfInterrupted_s{};
    // static_param at offset 0xe8
    const float* mDistanceResetGearInput_s{};
};

}  // namespace uking::ai
