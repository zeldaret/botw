#pragma once

#include "Game/AI/Action/actionSiteBossLswordAtk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossLswordAtkWithChemical : public SiteBossLswordAtk {
    SEAD_RTTI_OVERRIDE(SiteBossLswordAtkWithChemical, SiteBossLswordAtk)
public:
    explicit SiteBossLswordAtkWithChemical(const InitArg& arg);
    ~SiteBossLswordAtkWithChemical() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe8
    const int* mEmitNum_s{};
    // static_param at offset 0xf0
    const int* mEmitInterval_s{};
    // static_param at offset 0xf8
    const int* mEmitAttackDamage_s{};
    // static_param at offset 0x100
    const int* mEmitActorMinDamage_s{};
    // static_param at offset 0x108
    const float* mEmitOffsetFromParent_s{};
    // static_param at offset 0x110
    const float* mEmitIntervalDist_s{};
    // static_param at offset 0x118
    const float* mEmitIntervalRotate_s{};
    // static_param at offset 0x120
    const float* mEmitScale_s{};
    // static_param at offset 0x128
    const float* mEmitMaxScale_s{};
    // static_param at offset 0x130
    const float* mScaleTime_s{};
    // static_param at offset 0x138
    const float* mEmitStartFrame_s{};
    // static_param at offset 0x140
    const float* mEmitAngleFromParent_s{};
    // static_param at offset 0x148
    const float* mEmitActorSpeedRotate_s{};
    // static_param at offset 0x150
    sead::SafeString mEmitActorName_s{};
    // static_param at offset 0x160
    sead::SafeString mEmitPartsName_s{};
    // static_param at offset 0x170
    sead::SafeString mCallSEKeyAtAtOn_s{};
    // static_param at offset 0x180
    const sead::Vector3f* mEmitActorSpeed_s{};
};

}  // namespace uking::action
