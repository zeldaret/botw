#pragma once

#include "Game/AI/AI/aiEnemyDefaultReaction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SiteBossReaction : public EnemyDefaultReaction {
    SEAD_RTTI_OVERRIDE(SiteBossReaction, EnemyDefaultReaction)
public:
    explicit SiteBossReaction(const InitArg& arg);
    ~SiteBossReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const bool* mIsChangeEffectiveDamage_s{};
};

}  // namespace uking::ai
