#pragma once

#include "Game/AI/AI/aiNPCTravelBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCWander : public NPCTravelBase {
    SEAD_RTTI_OVERRIDE(NPCWander, NPCTravelBase)
public:
    explicit NPCWander(const InitArg& arg);
    ~NPCWander() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const float* mRainWaitTime_s{};
    // static_param at offset 0x80
    const float* mGoalDistance_s{};
    // static_param at offset 0x88
    const float* mRailUpdateDistRate_s{};
    // static_param at offset 0x90
    sead::SafeString mRainDestination_s{};
    // static_param at offset 0xa0
    sead::SafeString mNormalASKeyName_s{};
    // static_param at offset 0xb0
    sead::SafeString mRainASKeyName_s{};
    // static_param at offset 0xc0
    sead::SafeString mRailUniqueName_s{};
    // dynamic_param at offset 0xd0
    bool* mIsPathRest_d{};
};

}  // namespace uking::ai
