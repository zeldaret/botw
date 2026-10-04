#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EquipStand : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EquipStand, ksys::act::ai::Ai)
public:
    explicit EquipStand(const InitArg& arg);
    ~EquipStand() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x40];
    // static_param at offset 0x78
    sead::SafeString mDisplayAttKey_s{};
    // static_param at offset 0x88
    sead::SafeString mTakeOutAttKey_s{};
    // map_unit_param at offset 0x98
    const int* mEquipStandSlot_m{};
    // aitree_variable at offset 0xa0
    void* mEquipDisplayChild_a{};
};

}  // namespace uking::ai
