#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class PriestBossShadowCloneThrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(PriestBossShadowCloneThrow, ksys::act::ai::Ai)
public:
    explicit PriestBossShadowCloneThrow(const InitArg& arg);
    ~PriestBossShadowCloneThrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mShadowCloneOffsetY_s{};
    // static_param at offset 0x40
    const float* mShadowCloneRadius_s{};
    // static_param at offset 0x48
    const float* mShadowCloneAngleOffset_s{};
    // static_param at offset 0x50
    const float* mPrepareTimer_s{};
    // static_param at offset 0x58
    sead::SafeString mShadowCloneLefeBoneName_s{};
    // static_param at offset 0x68
    sead::SafeString mShadowCloneRightBoneName_s{};
    // aitree_variable at offset 0x78
    void* mPriestBossMetaAIUnit_a{};
};

}  // namespace uking::ai
