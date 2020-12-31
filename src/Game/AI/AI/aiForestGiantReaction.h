#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ForestGiantReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(ForestGiantReaction, EnemyDefaultReaction)
public:
    explicit ForestGiantReaction(const InitArg& arg);
    ~ForestGiantReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const int* mRightLegArmorSlot_s{};
    // static_param at offset 0x70
    const int* mLeftLegArmorSlot_s{};
    // static_param at offset 0x78
    sead::SafeString mTgLegL_s{};
    // static_param at offset 0x88
    sead::SafeString mBgLegL_s{};
    // static_param at offset 0x98
    sead::SafeString mTgLegR_s{};
    // static_param at offset 0xa8
    sead::SafeString mBgLegR_s{};
    // static_param at offset 0xb8
    sead::SafeString mTgArmR_s{};
};

}  // namespace uking::ai
