#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandwormBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandwormBattle, ksys::act::ai::Ai)
public:
    explicit SandwormBattle(const InitArg& arg);
    ~SandwormBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mAttackAngle_s{};
    // static_param at offset 0x40
    const float* mAttackInterval_s{};
    // static_param at offset 0x48
    const float* mAttackIntervalRand_s{};
    // static_param at offset 0x50
    const float* mBattleFailTimer_s{};
};

}  // namespace uking::ai
