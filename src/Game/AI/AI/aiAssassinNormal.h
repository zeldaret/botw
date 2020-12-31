#pragma once

#include "Game/AI/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(AssassinNormal, LandHumEnemyNormal)
public:
    explicit AssassinNormal(const InitArg& arg);
    ~AssassinNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
