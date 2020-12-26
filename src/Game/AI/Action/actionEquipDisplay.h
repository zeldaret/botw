#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EquipDisplay : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EquipDisplay, ksys::act::ai::Action)
public:
    explicit EquipDisplay(const InitArg& arg);
    ~EquipDisplay() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // FIXME: remove this
    u8 pad_0x20[0x28];
    // static_param at offset 0x48
    sead::SafeString mSwordEquipNode_s{};
    // static_param at offset 0x58
    sead::SafeString mLSwordEquipNode_s{};
    // static_param at offset 0x68
    sead::SafeString mSpearEquipNode_s{};
    // static_param at offset 0x78
    sead::SafeString mBowEquipNode_s{};
    // static_param at offset 0x88
    sead::SafeString mShieldEquipNode_s{};
    // map_unit_param at offset 0x98
    const int* mEquipStandSlot_m{};
    // map_unit_param at offset 0xa0
    sead::SafeString mEquipStandNode_m{};
    // aitree_variable at offset 0xb0
    void* mEquipDisplayChild_a{};
};

}  // namespace uking::action
