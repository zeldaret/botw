#pragma once

#include "Game/AI/AI/aiNPCTravelBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCTravel : public NPCTravelBase {
    SEAD_RTTI_OVERRIDE(NPCTravel, NPCTravelBase)
public:
    explicit NPCTravel(const InitArg& arg);
    ~NPCTravel() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const float* mWaitHorseReturnDist_s{};
    // static_param at offset 0x80
    const float* mGiveUpWaitHorseTime_s{};
};

}  // namespace uking::ai
