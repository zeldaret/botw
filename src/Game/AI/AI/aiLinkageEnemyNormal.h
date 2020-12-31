#pragma once

#include "Game/AI/AI/aiEnemyNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LinkageEnemyNormal : public EnemyNormal {
    SEAD_RTTI_OVERRIDE(LinkageEnemyNormal, EnemyNormal)
public:
    explicit LinkageEnemyNormal(const InitArg& arg);
    ~LinkageEnemyNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
