#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CommonPickedItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CommonPickedItem, ksys::act::ai::Ai)
public:
    explicit CommonPickedItem(const InitArg& arg);
    ~CommonPickedItem() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mCanGetOnBurning_s{};
    // static_param at offset 0x40
    const bool* mIsControlNoticeDo_s{};
    // static_param at offset 0x48
    sead::SafeString mGetAttKeyName_s{};
    // map_unit_param at offset 0x58
    const bool* mIsPlayerPut_m{};
    // map_unit_param at offset 0x60
    sead::SafeString mDropTable_m{};
    // map_unit_param at offset 0x70
    sead::SafeString mDropActor_m{};
    // aitree_variable at offset 0x80
    int* mGetNumLeft_a{};
};

}  // namespace uking::ai
