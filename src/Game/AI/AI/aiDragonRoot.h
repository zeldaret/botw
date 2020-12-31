#pragma once

#include "Game/AI/AI/aiDragonRootBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DragonRoot : public DragonRootBase {
    SEAD_RTTI_OVERRIDE(DragonRoot, DragonRootBase)
public:
    explicit DragonRoot(const InitArg& arg);
    ~DragonRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xc0
    const int* mChemicalBulletRate_s{};
    // static_param at offset 0xc8
    const int* mChemicalBulletNum_s{};
    // static_param at offset 0xd0
    const int* mUpdraftInterval_s{};
    // static_param at offset 0xd8
    const int* mReturnTime_s{};
    // static_param at offset 0xe0
    const int* mBodyHitDamage_s{};
    // static_param at offset 0xe8
    const int* mBodyHitPower_s{};
    // static_param at offset 0xf0
    const int* mBodyHitImpact_s{};
    // static_param at offset 0xf8
    const int* mBodyHitShieldDamage_s{};
    // static_param at offset 0x100
    const float* mOnRailDistance_s{};
    // static_param at offset 0x108
    const float* mFarDistance_s{};
    // static_param at offset 0x110
    const float* mSpeed_s{};
    // static_param at offset 0x118
    const float* mChemicalBulletArea_s{};
    // static_param at offset 0x120
    const float* mChemicalWindArea_s{};
    // static_param at offset 0x128
    const float* mChemicalWindPower_s{};
    // static_param at offset 0x130
    const float* mChemicalWindLimitHeight_s{};
    // static_param at offset 0x138
    const float* mUpdraftPower_s{};
    // static_param at offset 0x140
    const float* mUpdraftTime_s{};
    // static_param at offset 0x148
    const float* mUpdraftBoost_s{};
    // static_param at offset 0x150
    const float* mInitBackRailDistance_s{};
    // static_param at offset 0x158
    const bool* mIsEmitChemical_s{};
    // static_param at offset 0x160
    sead::SafeString mCommonTableName_s{};
    // static_param at offset 0x170
    sead::SafeString mTsunoTableName_s{};
    // static_param at offset 0x180
    sead::SafeString mTsumeTableName_s{};
    // static_param at offset 0x190
    sead::SafeString mKibaTableName_s{};
    // static_param at offset 0x1a0
    sead::SafeString mChemicalBulletActor_s{};
    // static_param at offset 0x1b0
    sead::SafeString mDefaultMaterialAnmName_s{};
    // static_param at offset 0x1c0
    sead::SafeString mHornAnmName_s{};
    // aitree_variable at offset 0x1d0
    sead::SafeString* mCreateRailName_a{};
};

}  // namespace uking::ai
