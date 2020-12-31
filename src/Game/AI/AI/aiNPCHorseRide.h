#pragma once

#include "Game/AI/AI/aiNonPlayerHorseRide.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCHorseRide : public NonPlayerHorseRide {
    SEAD_RTTI_OVERRIDE(NPCHorseRide, NonPlayerHorseRide)
public:
    explicit NPCHorseRide(const InitArg& arg);
    ~NPCHorseRide() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const int* mGearLevel_s{};
    // static_param at offset 0xe8
    const int* mGearResetPathNum_s{};
    // static_param at offset 0xf0
    const float* mPlayerNearDistance_s{};
    // aitree_variable at offset 0x268
    void* mEventBindUnit_a{};
};

}  // namespace uking::ai
