#pragma once

#include "Game/AI/AI/aiStalEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StalGiantEnemyRoot : public StalEnemyRoot {
    SEAD_RTTI_OVERRIDE(StalGiantEnemyRoot, StalEnemyRoot)
public:
    explicit StalGiantEnemyRoot(const InitArg& arg);
    ~StalGiantEnemyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x7c0
    sead::SafeString mActorNameChin_s{};
    // static_param at offset 0x7d0
    sead::SafeString mActorNameRib1_s{};
    // static_param at offset 0x7e0
    sead::SafeString mActorNameRib2_s{};
    // static_param at offset 0x7f0
    sead::SafeString mActorNameRib3_s{};
    // static_param at offset 0x800
    sead::SafeString mActorNameRib4_s{};
    // static_param at offset 0x810
    const bool* mIsDamageToEnemy_s{};
};

}  // namespace uking::ai
