#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRoamBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AnimalRoamBase, ksys::act::ai::Ai)
public:
    explicit AnimalRoamBase(const InitArg& arg);
    ~AnimalRoamBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSearchNextPathRadius_s{};
    // static_param at offset 0x40
    const float* mRadiusLimit_s{};
    // static_param at offset 0x48
    const float* mForwardDirDistCoefficient_s{};
    // static_param at offset 0x50
    const float* mDirRandomMinRatio_s{};
    // static_param at offset 0x58
    const float* mDirRangeAngle_s{};
    // static_param at offset 0x60
    const float* mRejectDistRatio_s{};
    // static_param at offset 0x68
    const float* mContinueAddSearchAngle_s{};
    // static_param at offset 0x70
    const float* mContinueReduceDistRatio_s{};
    // static_param at offset 0x78
    const float* mContinueReduceRejectDistRatio_s{};
    // map_unit_param at offset 0x80
    const float* mTerritoryArea_m{};
    // map_unit_param at offset 0x88
    const bool* mEnableNoEntryAreaCheck_m{};
    // aitree_variable at offset 0x90
    float* mFramesStuckOnTerrain_a{};
    // aitree_variable at offset 0x98
    bool* mIsStuckOnTerrain_a{};
};

}  // namespace uking::ai
