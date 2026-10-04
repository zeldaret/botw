#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GolemReaction, ksys::act::ai::Ai)
public:
    explicit GolemReaction(const InitArg& arg);
    ~GolemReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mClimbLimitTime_s{};
    // static_param at offset 0x40
    const int* mClampRestClimbTime_s{};
    // static_param at offset 0x48
    const int* mIgnoreBombTime_s{};
    // static_param at offset 0x50
    sead::SafeString mRightArmTgtBodyName_s{};
    // static_param at offset 0x60
    sead::SafeString mLeftArmTgtBodyName_s{};
    // static_param at offset 0x70
    sead::SafeString mBreakArmLXLinkKey_s{};
    // static_param at offset 0x80
    sead::SafeString mBodyArmLName1_s{};
    // static_param at offset 0x90
    sead::SafeString mBodyArmLName2_s{};
    // static_param at offset 0xa0
    sead::SafeString mChmArmLName_s{};
    // static_param at offset 0xb0
    sead::SafeString mArmLMaterialName_s{};
    // static_param at offset 0xc0
    sead::SafeString mBreakArmRXLinkKey_s{};
    // static_param at offset 0xd0
    sead::SafeString mBodyArmRName1_s{};
    // static_param at offset 0xe0
    sead::SafeString mBodyArmRName2_s{};
    // static_param at offset 0xf0
    sead::SafeString mChmArmRName_s{};
    // static_param at offset 0x100
    sead::SafeString mArmRMaterialName_s{};
    // aitree_variable at offset 0x110
    float* mGolemClimbedTime_a{};
    // aitree_variable at offset 0x118
    void* mGolemChemicalController_a{};
};

}  // namespace uking::ai
