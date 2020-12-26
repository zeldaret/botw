#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ItemAmiiboCreateFromDropTable : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ItemAmiiboCreateFromDropTable, ksys::act::ai::Action)
public:
    explicit ItemAmiiboCreateFromDropTable(const InitArg& arg);
    ~ItemAmiiboCreateFromDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mCreateInterval_s{};
    // static_param at offset 0x28
    const int* mClearSealNum_s{};
    // static_param at offset 0x30
    const int* mHitRateAdjustStart_s{};
    // static_param at offset 0x38
    const int* mHitRateAdjustEnd_s{};
    // static_param at offset 0x40
    const float* mCreateArea_s{};
    // static_param at offset 0x48
    const float* mBigHitRate1st_s{};
    // static_param at offset 0x50
    const float* mBigHitRate2nd_s{};
    // static_param at offset 0x58
    const float* mBigHitRate3rd_s{};
    // static_param at offset 0x60
    const float* mGreatHitRate1st_s{};
    // static_param at offset 0x68
    const float* mGreatHitRate2nd_s{};
    // static_param at offset 0x70
    const float* mGreatHitRate3rd_s{};
    // static_param at offset 0x78
    const float* mDropNumRate1st_s{};
    // static_param at offset 0x80
    const float* mDropNumRate2nd_s{};
    // static_param at offset 0x88
    const float* mDropNumRate3rd_s{};
    // static_param at offset 0x90
    const float* mSmallHitRate1st_s{};
    // static_param at offset 0x98
    const float* mSmallHitRate2nd_s{};
    // static_param at offset 0xa0
    const float* mSmallHitRate3rd_s{};
    // static_param at offset 0xa8
    sead::SafeString mPairActor_0_s{};
    // static_param at offset 0xb8
    sead::SafeString mPairActor_1_s{};
    // static_param at offset 0xc8
    sead::SafeString mPairActor_2_s{};
    // static_param at offset 0xd8
    sead::SafeString mFlagActor_0_s{};
    // static_param at offset 0xe8
    sead::SafeString mFlagActor_1_s{};
    // static_param at offset 0xf8
    sead::SafeString mFlagActor_2_s{};
    // static_param at offset 0x108
    sead::SafeString mNotFlagActor_0_s{};
    // static_param at offset 0x118
    sead::SafeString mNotFlagActor_1_s{};
    // static_param at offset 0x128
    const sead::Vector3f* mCreateOffset_s{};
};

}  // namespace uking::action
