#pragma once

#include "Game/AI/AI/aiDragonRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonIceRoot : public DragonRoot {
    SEAD_RTTI_OVERRIDE(DragonIceRoot, DragonRoot)
public:
    explicit DragonIceRoot(const InitArg& arg);
    ~DragonIceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x270
    const int* mGrudgeBulletMaxNum_s{};
    // static_param at offset 0x278
    const int* mGrudgeBulletMinInterval_s{};
    // static_param at offset 0x280
    const int* mGrudgeSmokeTime_s{};
    // static_param at offset 0x288
    const float* mGrudgeEventRail_pre1stSpeed_s{};
    // static_param at offset 0x290
    const float* mGrudgeEventRail_1stSpeed_s{};
    // static_param at offset 0x298
    const float* mGrudgeEventRail_pre2ndSpeed_s{};
    // static_param at offset 0x2a0
    const float* mGrudgeEventRail_2ndSpeed_s{};
    // static_param at offset 0x2a8
    const float* mGrudgeEventRail_pre3rdSpeed_s{};
    // static_param at offset 0x2b0
    const float* mGrudgeEventRail_3rdSpeed_s{};
    // static_param at offset 0x2b8
    const float* mGrudgeEventRail_preEndSpeed_s{};
    // static_param at offset 0x2c0
    const float* mGrudgeEventRail_EndSpeed_s{};
    // static_param at offset 0x2c8
    const float* mGrudgeEventRail_ReturnSpeed_s{};
    // static_param at offset 0x2d0
    const float* mGrudgeBulletRate_s{};
    // static_param at offset 0x2d8
    sead::SafeString mGrudgeEventRail_Start_s{};
    // static_param at offset 0x2e8
    sead::SafeString mGrudgeEventRail_pre1st_s{};
    // static_param at offset 0x2f8
    sead::SafeString mGrudgeEventRail_1st_s{};
    // static_param at offset 0x308
    sead::SafeString mGrudgeEventRail_pre2nd_s{};
    // static_param at offset 0x318
    sead::SafeString mGrudgeEventRail_2nd_s{};
    // static_param at offset 0x328
    sead::SafeString mGrudgeEventRail_pre3rd_s{};
    // static_param at offset 0x338
    sead::SafeString mGrudgeEventRail_3rd_s{};
    // static_param at offset 0x348
    sead::SafeString mGrudgeEventRail_preEnd_s{};
    // static_param at offset 0x358
    sead::SafeString mGrudgeEventRail_End_s{};
    // static_param at offset 0x368
    sead::SafeString mGrudgeEventRail_ReturnToSky_s{};
    // static_param at offset 0x378
    sead::SafeString mGrudgeBulletActorName_s{};
};

}  // namespace uking::ai
