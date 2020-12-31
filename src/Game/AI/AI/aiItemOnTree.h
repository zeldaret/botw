#pragma once

#include "Game/AI/AI/aiItemRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ItemOnTree : public ItemRoot {
    SEAD_RTTI_OVERRIDE(ItemOnTree, ItemRoot)
public:
    explicit ItemOnTree(const InitArg& arg);
    ~ItemOnTree() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x50
    const int* mFallPowerMin_s{};
    // static_param at offset 0x58
    const int* mFallPowerMax_s{};
    // static_param at offset 0x60
    const int* mFallOddsMin_s{};
    // static_param at offset 0x68
    const int* mFallOddsMax_s{};
    // static_param at offset 0x70
    const float* mFallIntervalRange_s{};
    // static_param at offset 0x78
    const float* mFallCheckSpeedTh_s{};
    // static_param at offset 0x80
    sead::SafeString mAttOnTree_s{};
    // static_param at offset 0x90
    sead::SafeString mAttOnGround_s{};
};

}  // namespace uking::ai
