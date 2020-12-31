#pragma once

#include "Game/AI/AI/aiBreathAttackEnemyBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MiniBeamAttack : public BreathAttackEnemyBattle {
    SEAD_RTTI_OVERRIDE(MiniBeamAttack, BreathAttackEnemyBattle)
public:
    explicit MiniBeamAttack(const InitArg& arg);
    ~MiniBeamAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb0
    const float* mFluctuationRange_s{};
    // static_param at offset 0xb8
    const float* mFluctuationSpan_s{};
    // static_param at offset 0xc0
    const float* mTargetOffsetY_s{};
    // static_param at offset 0xc8
    sead::SafeString mNodeName_s{};
    // static_param at offset 0xd8
    const bool* mIsValidGuide_s{};
    // static_param at offset 0xe0
    const bool* mIsIgnoreSmallHit_s{};
    // static_param at offset 0xe8
    const bool* mIsChangeable_s{};
    // static_param at offset 0xf0
    sead::SafeString mAimEffectName_s{};
};

}  // namespace uking::ai
