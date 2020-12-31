#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WizzrobeRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WizzrobeRoam, ksys::act::ai::Ai)
public:
    explicit WizzrobeRoam(const InitArg& arg);
    ~WizzrobeRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // aitree_variable at offset 0x38
    void* mWizzrobeMagicWeatherUnit_a{};
    // static_param at offset 0x40
    const int* mMoveCountMin_s{};
    // static_param at offset 0x48
    const int* mMoveCountMax_s{};
    // static_param at offset 0x50
    const int* mChangeHeightPer_s{};
    // static_param at offset 0x58
    const int* mMexHeightLevel_s{};
    // static_param at offset 0x60
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x68
    const float* mTerritoryRadiusRnd_s{};
    // static_param at offset 0x70
    const float* mRetryLength_s{};
    // static_param at offset 0x78
    const float* mHeightOffset_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mCentralPos_d{};
};

}  // namespace uking::ai
