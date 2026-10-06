#pragma once

#include "Game/Actor/AI/aiLandHumEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GuardHomePosNormal : public LandHumEnemyNormal {
    SEAD_RTTI_OVERRIDE(GuardHomePosNormal, LandHumEnemyNormal)
public:
    explicit GuardHomePosNormal(const InitArg& arg);
    ~GuardHomePosNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
