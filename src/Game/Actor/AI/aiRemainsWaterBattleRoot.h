#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsWaterBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterBattleRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWaterBattleRoot(const InitArg& arg);
    ~RemainsWaterBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mCallClearDemoTimer_s{};
    // static_param at offset 0x40
    const float* mAfterDamageTimer_s{};
    // static_param at offset 0x48
    const float* mAfterPaooonTimer_s{};
    // static_param at offset 0x50
    const float* mAfterHellTimer_s{};
    // static_param at offset 0x58
    const float* mFirstBulletTimer_s{};
    // aitree_variable at offset 0x60
    void* mRemainsWaterBattleInfo_a{};
};

}  // namespace uking::ai
