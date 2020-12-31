#pragma once

#include "Game/AI/AI/aiMiniBeamAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardianMiniBeamAttack : public MiniBeamAttack {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttack, MiniBeamAttack)
public:
    explicit GuardianMiniBeamAttack(const InitArg& arg);
    ~GuardianMiniBeamAttack() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x250
    sead::SafeString mHeadNodeName_s{};
    // static_param at offset 0x260
    const int* mAttackInterval_s{};
    // static_param at offset 0x268
    const int* mEndShaderASFrame_s{};
    // static_param at offset 0x270
    sead::SafeString mLoopShaderASName_s{};
    // static_param at offset 0x280
    sead::SafeString mEndShaderASName_s{};
    // static_param at offset 0x290
    sead::SafeString mPreLaunchEffectName_s{};
    // static_param at offset 0x2a0
    const bool* mIsChangeable_s{};
    // static_param at offset 0x2a8
    const bool* mIsFinalBattle_s{};
    // static_param at offset 0x2b0
    const float* mInDirAngle_s{};
};

}  // namespace uking::ai
