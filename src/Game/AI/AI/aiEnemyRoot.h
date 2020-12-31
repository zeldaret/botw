#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyRoot, ksys::act::ai::Ai)
public:
    explicit EnemyRoot(const InitArg& arg);
    ~EnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x8];
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mOutOfWaterOffset_s{};
    // static_param at offset 0x50
    const float* mSpreadDist_s{};
    // static_param at offset 0x58
    const float* mSmallSpreadDist_s{};
    // static_param at offset 0x60
    const bool* mIgnoreHell_s{};
    // static_param at offset 0x68
    sead::SafeString mFortressTag_s{};
    // map_unit_param at offset 0x78
    const bool* mIsNearCreate_m{};
    // map_unit_param at offset 0x80
    sead::SafeString mEquipItem1_m{};
    // map_unit_param at offset 0x90
    sead::SafeString mEquipItem2_m{};
    // map_unit_param at offset 0xa0
    sead::SafeString mEquipItem3_m{};
    // map_unit_param at offset 0xb0
    sead::SafeString mEquipItem4_m{};
    // map_unit_param at offset 0xc0
    sead::SafeString mRideHorseName_m{};
    // aitree_variable at offset 0xd0
    int* mCreateDeadConditionType_a{};
    // aitree_variable at offset 0xd8
    int* mForceSealSilentKillCount_a{};
    // aitree_variable at offset 0xe0
    bool* mIsTrgChangeUnderWaterState_a{};
};

}  // namespace uking::ai
