#pragma once

#include "Game/AI/AI/aiLynelBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class CastleLynelBattle : public LynelBattle {
    SEAD_RTTI_OVERRIDE(CastleLynelBattle, LynelBattle)
public:
    explicit CastleLynelBattle(const InitArg& arg);
    ~CastleLynelBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
