#pragma once

#include "Game/AI/AI/aiAssassinBossIronBallAttack.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinBossLastAttack : public AssassinBossIronBallAttack {
    SEAD_RTTI_OVERRIDE(AssassinBossLastAttack, AssassinBossIronBallAttack)
public:
    explicit AssassinBossLastAttack(const InitArg& arg);
    ~AssassinBossLastAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
