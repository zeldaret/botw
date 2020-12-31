#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GolemNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(GolemNormal, EnemyNormal)
public:
    explicit GolemNormal(const InitArg& arg);
    ~GolemNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
