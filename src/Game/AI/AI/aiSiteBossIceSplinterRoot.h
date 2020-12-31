#pragma once

#include "Game/AI/AI/aiSiteBossChemicalProjectile.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossIceSplinterRoot : public SiteBossChemicalProjectile {
    SEAD_RTTI_OVERRIDE(SiteBossIceSplinterRoot, SiteBossChemicalProjectile)
public:
    explicit SiteBossIceSplinterRoot(const InitArg& arg);
    ~SiteBossIceSplinterRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x180
    const int* mReflectAtkPower_s{};
    // static_param at offset 0x188
    const float* mChaseAngleMin_s{};
    // static_param at offset 0x190
    const float* mRotateSpeed_s{};
    // static_param at offset 0x198
    sead::SafeString mBindNodeName0_s{};
    // static_param at offset 0x1a8
    sead::SafeString mBindNodeName1_s{};
    // static_param at offset 0x1b8
    sead::SafeString mChaseParentNode_s{};
    // static_param at offset 0x1c8
    const sead::Vector3f* mBindOffset0_s{};
    // static_param at offset 0x1d0
    const sead::Vector3f* mBindOffset1_s{};
    // static_param at offset 0x1d8
    const sead::Vector3f* mBindOffset2_s{};
    // static_param at offset 0x1e0
    const sead::Vector3f* mBindOffset3_s{};
    // static_param at offset 0x1e8
    const sead::Vector3f* mBindOffset4_s{};
    // static_param at offset 0x1f0
    const sead::Vector3f* mBindOffset5_s{};
    // static_param at offset 0x1f8
    const sead::Vector3f* mBindOffset6_s{};
    // static_param at offset 0x200
    const sead::Vector3f* mBindOffset7_s{};
    // static_param at offset 0x208
    const sead::Vector3f* mBindOffset8_s{};
    // static_param at offset 0x210
    const sead::Vector3f* mRotateSpeedAtHit_s{};
    // static_param at offset 0x218
    const sead::Vector3f* mRotateSpeedAtFall_s{};
    // map_unit_param at offset 0x220
    const int* mCount_m{};
};

}  // namespace uking::ai
