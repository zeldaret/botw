#pragma once

#include "Game/AI/AI/aiRememberMesOneActorEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinShooterJuniorAzitoRoot : public RememberMesOneActorEnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinShooterJuniorAzitoRoot, RememberMesOneActorEnemyRoot)
public:
    explicit AssassinShooterJuniorAzitoRoot(const InitArg& arg);
    ~AssassinShooterJuniorAzitoRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
