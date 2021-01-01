#pragma once

#include "Game/AI/Action/actionGanonThrowFireBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GanonThrowMultiIce : public GanonThrowFireBall {
    SEAD_RTTI_OVERRIDE(GanonThrowMultiIce, GanonThrowFireBall)
public:
    explicit GanonThrowMultiIce(const InitArg& arg);
    ~GanonThrowMultiIce() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xd0
    const int* mThrowNumAtSameTiming_s{};
    // dynamic_param at offset 0xd8
    sead::SafeString mThrowPartsName1_d{};
    // dynamic_param at offset 0xe8
    sead::SafeString mThrowPartsName2_d{};
    // dynamic_param at offset 0xf8
    sead::SafeString mThrowPartsName3_d{};
    // dynamic_param at offset 0x108
    sead::SafeString mThrowPartsName4_d{};
    // dynamic_param at offset 0x118
    sead::SafeString mThrowPartsName5_d{};
    // dynamic_param at offset 0x128
    sead::SafeString mThrowPartsName6_d{};
    // dynamic_param at offset 0x138
    sead::SafeString mThrowPartsName7_d{};
    // dynamic_param at offset 0x148
    sead::SafeString mThrowPartsName8_d{};
};

}  // namespace uking::action
