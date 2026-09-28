#pragma once

#include "Game/Actor/AI/aiAssassinShooterBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinFieldShooterBattle : public AssassinShooterBattle {
    SEAD_RTTI_OVERRIDE(AssassinFieldShooterBattle, AssassinShooterBattle)
public:
    explicit AssassinFieldShooterBattle(const InitArg& arg);
    ~AssassinFieldShooterBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
