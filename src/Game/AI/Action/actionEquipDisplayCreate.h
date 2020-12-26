#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipDisplayCreate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EquipDisplayCreate, ksys::act::ai::Action)
public:
    explicit EquipDisplayCreate(const InitArg& arg);
    ~EquipDisplayCreate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mDelayTimer_s{};
    // static_param at offset 0x28
    sead::SafeString mSwordEquipNode_s{};
    // static_param at offset 0x38
    sead::SafeString mLSwordEquipNode_s{};
    // static_param at offset 0x48
    sead::SafeString mSpearEquipNode_s{};
    // static_param at offset 0x58
    sead::SafeString mBowEquipNode_s{};
    // static_param at offset 0x68
    sead::SafeString mShieldEquipNode_s{};
    // static_param at offset 0x78
    sead::SafeString mXLinkKey_s{};
    // map_unit_param at offset 0x88
    const int* mEquipStandSlot_m{};
    // map_unit_param at offset 0x90
    sead::SafeString mEquipStandNode_m{};
    // aitree_variable at offset 0xa0
    void* mEquipDisplayChild_a{};
};

}  // namespace uking::action
