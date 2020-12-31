#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OnCliffEnemyBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OnCliffEnemyBattle, ksys::act::ai::Ai)
public:
    explicit OnCliffEnemyBattle(const InitArg& arg);
    ~OnCliffEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostCounter_s{};
    // static_param at offset 0x40
    const float* mAttackDist_s{};
    // static_param at offset 0x48
    const float* mAttackAngleH_s{};
    // static_param at offset 0x50
    const float* mAttackAngleVMax_s{};
    // static_param at offset 0x58
    const float* mAttackAngleVMin_s{};
    // static_param at offset 0x60
    const float* mAttackIntervalIntensity_s{};
};

}  // namespace uking::ai
