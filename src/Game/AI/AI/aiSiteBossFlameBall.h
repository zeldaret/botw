#pragma once

#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossFlameBall : public SiteBossChemicalProjectile {
    SEAD_RTTI_OVERRIDE(SiteBossFlameBall, SiteBossChemicalProjectile)
public:
    explicit SiteBossFlameBall(const InitArg& arg);
    ~SiteBossFlameBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x180
    const int* mChemicalIndex_s{};
    // static_param at offset 0x188
    const int* mAtAttr_s{};
    // static_param at offset 0x190
    const float* mMoveSpeed_s{};
    // static_param at offset 0x198
    const float* mMoveOffset_s{};
    // static_param at offset 0x1a0
    const float* mCountOffset_s{};
    // static_param at offset 0x1a8
    const bool* mIsInfluence_s{};
    // map_unit_param at offset 0x1b0
    const int* mCount_m{};
    // map_unit_param at offset 0x1b8
    const sead::Vector3f* mPosOffset_m{};
};

}  // namespace uking::ai
